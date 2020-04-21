#include "model.h"
#include "collection.h"
#include "builder.h"
#include <QJsonObject>
Model::Model(const QString &table, const PrimaryKey &primarykey, const QString &modelName, bool usesTimeStamps, bool usesIncrementing) : _exists(false),
    _table(table),_primaryKey(primarykey),_modelName(modelName),_useTimeStamps(usesTimeStamps),_incrementing(usesIncrementing)
{

}

//Model::Model(const QMap<QString, QVariant> &map) : _exists(false),data(map)
//{

//}
Model::~Model()
{

}

void Model::set(QString key, QVariant value)
{
    data.insert(key,value);
}

QVariant Model::get(QString key) const
{
    return data.value(key);
}


void Model::setSaved()
{
    _exists=true;
    original=data;
}

bool Model::usesTimestamps() const
{
    return _useTimeStamps;
}



QVariant Model::operator[](const QString key)
{
    return get(key);
}

ModelBuilder Model::builder() const
{
    return ModelBuilder(*this);
}

bool Model::save()
{
    return exists() ? builder().update(*this) : builder().insert(*this);
}

bool Model::remove()
{
    return builder().remove(*this);
}

Model::operator QVariant()
{
    return operator QJsonObject();
}

Model::operator QJsonObject()
{
    return QJsonObject::fromVariantMap(data);
}

//ModelBuilder Model::with(const Relation &relation)
//{
//    return builder().with(relation);
//}

QStringList Model::dirtyKeys() const
{
    QStringList dirtyKeys;
    for (const QString &key : keys()) {
     if((original[key]!=data[key]) || original.count(key) == 0)
         dirtyKeys << key;
    }
    return dirtyKeys;
}

