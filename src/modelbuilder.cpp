#include "modelbuilder.h"
#include "model.h"
#include "collection.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDateTime>
#include "relations/relation.h"
#include <QDebug>
#include <QSharedPointer>
ModelBuilder::ModelBuilder(const Model &model) :_model(new Model(model)),_builder(_model->table())
{

}

ModelBuilder::ModelBuilder(const ModelBuilder &other) : _model(new Model(*other._model)),_builder(other._builder),relations(other.relations)
{

}

ModelBuilder::~ModelBuilder()
{
//    if(_model)
//        delete _model;
}

ModelBuilder::ModelBuilder(const QString &table, const QString &primaryKey, const QString &modelName, const bool &usesTimestamps) :
    _model(new Model(table,primaryKey,modelName,usesTimestamps)),_builder(table)
{

}

//ModelBuilder::ModelBuilder(const ModelBuilder &other) : _builder(other.table())
//{

//}

Model ModelBuilder::model() const
{
    return *_model;
}



Collection ModelBuilder::get(const QVariant &column)
{
    qDebug()<<"Called";
//    if(column.isValid())
//    {
//        switch (column.type()) {
//        case QMetaType::QStringList : builder().select(column.toStringList()); break;
//        case QMetaType::QString     : builder().select(column.toString())    ; break;
//        default:                                                               break;
//        }
//    }


    QSqlQuery query=builder().get();
    if(query.exec())
    {
        Collection collection;
        QSqlRecord record=query.record();
        while (query.next()) {
            Model m(model());
            for(int i=0; i<record.count(); i++)
            {
                m.set(record.fieldName(i),query.value(i));
                m.setSaved();
            }
            collection << m;

        }

        qDebug()<<"Reached";

        for(auto ptr : relations)
        {
            Relation *relation=ptr.data();
            relation->addConstraints(collection);
            relation->match(collection);
        }



        return collection;
    }
    return Collection();
}

ModelBuilder &ModelBuilder::where(QString key, QVariant value)
{
    builder().where(key,value);
    return *this;
}

ModelBuilder &ModelBuilder::where(QString key, QString op, QVariant value)
{
    builder().where(key,op,value);
    return *this;
}

ModelBuilder &ModelBuilder::where(QString clause)
{
    builder().where(clause);
    return *this;
}

ModelBuilder &ModelBuilder::whereIn(QString key, QVariantList values)
{
    builder().whereIn(key,values);

    return *this;
}

ModelBuilder &ModelBuilder::with(const Relation &relation)
{
    relations << QSharedPointer<Relation>(relation.clone());
    return *this;
}

bool ModelBuilder::insert(Model &mdl)
{
    if(mdl.usesTimestamps())
    {
        QDateTime now=QDateTime::currentDateTime();
        mdl.set("created_at",now);
        mdl.set("updated_at",now);
        mdl.setSaved();
    }

    return builder().where(model().primaryKey(),get(model().primaryKey())).insert(mdl.original);
}

bool ModelBuilder::update(Model &mdl)
{
    if(mdl.usesTimestamps())
    {
        QDateTime now=QDateTime::currentDateTime();
        mdl.set("updated_at",now);
    }

    bool result = builder().where(model().primaryKey(),get(model().primaryKey())).update(mdl.data);

    mdl.setSaved();

    return result;
}

bool ModelBuilder::remove(const Model &model)
{
    //implement me
}

