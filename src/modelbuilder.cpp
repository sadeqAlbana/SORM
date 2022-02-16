/*
 * Copyright (C) 2022 Sadeq Albana
 *
 * Licensed under the GNU Lesser General Public License v3.0 :
 * https://www.gnu.org/licenses/lgpl-3.0.html
 */

#include "modelbuilder.h"
#include "model.h"
#include "collection.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDateTime>
#include "relations/relation.h"
#include <QDebug>
#include <QSharedPointer>
#include <QSqlError>
#include "relations/relationlist.h"
ModelBuilder::ModelBuilder(const Model &model) :_model(new Model(model)),_builder(_model->table())
{

}

ModelBuilder::ModelBuilder(const ModelBuilder &other) : _model(new Model(*other._model)),_builder(other._builder),relations(other.relations)
{

}

ModelBuilder::~ModelBuilder()
{
        delete _model;
}

ModelBuilder::ModelBuilder(const QString &table, const PrimaryKey &primaryKey, const QString &modelName, const bool &usesTimestamps, const bool &usesAutoIncrement) :
    _model(new Model(table,primaryKey,modelName,usesTimestamps,usesAutoIncrement)),_builder(table)
{

}

Model ModelBuilder::model() const
{
    return *_model;
}



Collection ModelBuilder::get(const QVariant &column)
{
    if(column.isValid())
    {
        switch (column.type()) {
        case QMetaType::QStringList : builder().select(column.toStringList()); break;
        case QMetaType::QString     : builder().select(column.toString())    ; break;
        default:                                                               break;
        }
    }

    if(model().usesTimestamps()){
        builder().whereRaw(QString("%1 is null").arg(builder().escapeKey("deleted_at")));
    }
    QSqlQuery query=builder().get();
    if(query.lastError().type()==QSqlError::NoError) //was if(query.exec()).........possible bug ?
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

        if(!collection.isEmpty()){
            for(Relation *relation : relations)
            {
                relation->addConstraints(collection);
                relation->match(collection);
            }
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

ModelBuilder &ModelBuilder::whereRaw(QString clause)
{
    builder().whereRaw(clause);
    return *this;
}

ModelBuilder &ModelBuilder::whereIn(QString key, QVariantList values)
{
    builder().whereIn(key,values);

    return *this;
}

ModelBuilder &ModelBuilder::whereIn(QString key, QString subQuery)
{
    builder().whereIn(key,subQuery);

    return *this;
}

ModelBuilder &ModelBuilder::with(const Relation &relation)
{
    relations << relation.clone();
    return *this;
}

ModelBuilder &ModelBuilder::with(const RelationList &relations)
{
    for(const Relation * const &relation : relations){
        this->relations << relation->clone();
    }
    return *this;
}

ModelBuilder &ModelBuilder::groupBy(QString column)
{
    builder().groupBy(column);
    return *this;
}

ModelBuilder &ModelBuilder::orderBy(QString column)
{
    builder().groupBy(column);
    return *this;
}



Model ModelBuilder::first()
{
    builder().take(1);
    return get().value(0);
}

bool ModelBuilder::insert(Model &mdl)
{
    if(mdl.usesTimestamps())
    {
        QDateTime now=QDateTime::currentDateTime();
        mdl.set("created_at",now);
        mdl.set("updated_at",now);
    }

    bool success= builder().insert(mdl.data);
    if(success){
        QVariant lastInsertId=builder().lastInsertId();
        if(lastInsertId.isValid() && mdl._incrementing){
            mdl.set(mdl.primaryKey().toString(),lastInsertId);
        }
        mdl.setSaved();
    }
    return success;
}

bool ModelBuilder::update(Model &mdl)
{
    if(mdl.usesTimestamps())
    {
        QDateTime now=QDateTime::currentDateTime();
        mdl.set("updated_at",now);
    }


    QVariantMap updateData;
    for (auto key : mdl.dirtyKeys()) {
     updateData[key]=mdl[key];
    }

    if(mdl.primaryKey().isList())
    {
        QStringList primaryKeys=mdl.primaryKey().toStringList();
        for(const QString &key : primaryKeys){
            builder().where(key,mdl.get(key));
        }
    }
    else{
       builder().where(model().primaryKey().toString(),mdl.get(model().primaryKey().toString()));
    }


    bool result=builder().update(updateData);
    mdl.setSaved();

    return result;
}

bool ModelBuilder::remove(Model &model)
{
    if(!model.exists())
        return false;

    if(model.primaryKey().isList()){
        QStringList primaryKeys=model.primaryKey().toStringList();
        for(const QString &key : primaryKeys){
            builder().where(key,model.get(key));
        }
    }
    else
        builder().where(model.primaryKey().toString(),model.get(model.primaryKey().toString()));


    bool success=false;
    if(model.usesTimestamps()){
        model.set("deleted_at",QDateTime::currentDateTime());
        success=update(model);
    }else{
        success=builder().remove();
    }

    if(success){
        model._exists=false;
    }

    return success;
}

ModelBuilder &ModelBuilder::paginate(int page, int count)
{
    builder().paginate(page,count);

    return *this;
}

