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

bool Model::save()
{

}

bool Model::usesTimestamps()
{
    return true;
}

QVariant Model::operator[](const QString key)
{
    return get(key);
}


