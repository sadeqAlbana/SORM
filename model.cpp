#include "model.h"
#include "collection.h"
#include "builder.h"
Model::Model()
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


