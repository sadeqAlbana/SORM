#include "model.h"

Model::Model()
{

}

void Model::set(QString key, QVariant value)
{
    data.insert(key,value);

}

QVariant Model::get(QString key)
{
    return data.value(key);
}

bool Model::save()
{

}

