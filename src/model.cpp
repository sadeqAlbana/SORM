/*
 * Copyright (C) 2022 Sadeq Albana
 *
 * Licensed under the GNU Lesser General Public License v3.0 :
 * https://www.gnu.org/licenses/lgpl-3.0.html
 */

#include "model.h"
#include <QJsonObject>
#include <QDateTime>
Model::Model(const QString &table, const PrimaryKey &primarykey, const QString &modelName, bool usesTimeStamps, bool usesIncrementing) :
    d(new ModelData(table,primarykey,modelName,usesTimeStamps,usesIncrementing))

{
}



//Model::Model(const QMap<QString, QVariant> &map) : _exists(false),data(map)
//{

//}


void Model::set(QString key, QVariant value)
{
    d->data.insert(key,value);
}

QVariant Model::get(const QString &key) const
{
    return d->data.value(key);
}


void Model::setSaved()
{
    d->_exists=true;
    d->original=d->data;
}

bool Model::usesTimestamps() const
{
    return d->_useTimeStamps;
}


QVariant Model::operator [](const QString key) const
{
    return d->data[key];
}

QVariant& Model::operator [](const QString key)
{
    return d->data[key];
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

Model::operator QJsonValue() const
{
    return QJsonValue(operator QJsonObject());
}

Model::operator QVariant() const
{
    return QVariant::fromValue<Model>(*this);
}

Model::operator QJsonObject()  const
{
    QJsonObject object;
    QMapIterator it(d->data);
    while (it.hasNext()){
        it.next();
        if(it.value().canConvert<Model>()){
            object.insert(it.key(),it.value().value<Model>().operator QJsonObject());
        }else{
            object.insert(it.key(),QJsonValue::fromVariant(it.value()));
        }
    }
    return object;
//    return QJsonObject::fromVariantMap(d->data);
}

//ModelBuilder Model::with(const Relation &relation)
//{
//    return builder().with(relation);
//}

QStringList Model::dirtyKeys() const
{
    QStringList dirtyKeys;
    for (const QString &key : keys()) {
     if((d->original[key]!=d->data[key]) || d->original.count(key) == 0)
         dirtyKeys << key;
    }
    return dirtyKeys;
}

QDateTime Model::created_at() const
{
    return get("created_at").toDateTime();
}

QDebug operator<<(QDebug dbg, const Model &model)
{
    QDebugStateSaver saver(dbg);
    for(int i=0; i<model.keys().count(); i++){
     dbg.nospace()<<QString("%1:%2, ").arg(model.keys().at(i),model[model.keys().at(i)].toString());
    }

    return dbg;
}
