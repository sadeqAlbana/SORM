#include "model.h"
#include "collection.h"
#include "builder.h"
#include <QJsonObject>
#include "relations/hasmanyrelation.h"
#include "relations/relation.h"
//Model::Model(const Model &other, const QString tbl, const QString pk): _exists(other._exists), data(other.data),original(other.original),_useTimeStamps(other._useTimeStamps)
//{

//}

Model::Model(const QString tbl, const QString pk, const QString modelName) : _exists(false),_table(tbl),_primaryKey(pk),_modelName(modelName)
{

}

Model::Model(const QMap<QString, QVariant> &map, const QString tbl, const QString pk,const QString modelName) : _exists(false),data(map),_table(tbl),_primaryKey(pk),_modelName(modelName)
{

}
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

bool Model::usesTimestamps()
{
    return _useTimeStamps;
}



QVariant Model::operator[](const QString key)
{
    return get(key);
}

Model::operator QVariant()
{
    return operator QJsonObject();
}

Model::operator QJsonObject()
{
    QJsonObject object;

    for(const QString &key : keys())
        object[key]=get(key).toString();

    return object;
}

QStringList Model::dirtyKeys() const
{
    QStringList dirtyKeys;
    for (const QString &key : keys()) {
     if((original[key]!=data[key]) || original.count(key) == 0)
         dirtyKeys << key;
    }
    return dirtyKeys;
}



