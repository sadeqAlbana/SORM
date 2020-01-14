#include "model.h"
#include "collection.h"
#include "builder.h"
Model::Model() : _exists(false)
{

}

Model::Model(const QMap<QString, QVariant> &map) : _exists(false),data(map)
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

QStringList Model::dirtyKeys() const
{
    QStringList dirtyKeys;
    for (const QString &key : keys()) {
     if((original[key]!=data[key]) || original.count(key) == 0)
         dirtyKeys << key;
    }
    return dirtyKeys;
}


