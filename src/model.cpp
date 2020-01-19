#include "model.h"
#include "collection.h"
#include "builder.h"
Model::Model(const QString &table, const QString &primarykey, const QString &modelName, bool usesTimeStamps) : _exists(false),
    _table(table),_primaryKey(primarykey),_modelName(modelName),_useTimeStamps(usesTimeStamps)
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

ModelBuilder Model::builder()
{
    return ModelBuilder(*this);
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

