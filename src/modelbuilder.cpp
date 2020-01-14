#include "modelbuilder.h"
#include "model.h"
#include "collection.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDateTime>
ModelBuilder::ModelBuilder(const Model &model) : _table(model.table()),
    _primaryKey(model.primaryKey()), _modelName(model.modelName()),_builder(table())
{

}

ModelBuilder::ModelBuilder(const QString &table, const QString &primaryKey, const QString &modelName) : _table(table),
    _primaryKey(primaryKey), _modelName(modelName),_builder(table)
{

}

Model ModelBuilder::model()
{
    return Model(table(),primaryKey(),modelName());
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


    QSqlQuery query=builder().get();
    if(query.exec())
    {
        Collection collection;
        QSqlRecord record=query.record();
        while (query.next()) {
            Model m(table(),primaryKey(),modelName(),usesTimestamps());
            for(int i=0; i<record.count(); i++)
            {
                m.set(record.fieldName(i),query.value(i));
                m.setSaved();
            }
            collection << m;

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

bool ModelBuilder::insert(Model &model)
{
    if(model.usesTimestamps())
    {
        QDateTime now=QDateTime::currentDateTime();
        model.set("created_at",now);
        model.set("updated_at",now);
        model.setSaved();
    }

    return builder().where(primaryKey(),get(primaryKey())).insert(model.original);
}

bool ModelBuilder::update(Model &model)
{
    if(model.usesTimestamps())
    {
        QDateTime now=QDateTime::currentDateTime();
        model.set("updated_at",now);
    }

    bool result = builder().where(primaryKey(),get(primaryKey())).update(model.data);

    model.setSaved();

    return result;
}

bool ModelBuilder::usesTimestamps() const
{
    return _usesTimestamps;
}

QString ModelBuilder::table() const
{
    return _table;
}

QString ModelBuilder::primaryKey() const
{
    return _primaryKey;
}

QString ModelBuilder::modelName() const
{
    return _modelName;
}
