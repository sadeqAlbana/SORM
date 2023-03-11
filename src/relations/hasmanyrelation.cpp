/*
 * Copyright (C) 2022 Sadeq Albana
 *
 * Licensed under the GNU Lesser General Public License v3.0 :
 * https://www.gnu.org/licenses/lgpl-3.0.html
 */

#include "hasmanyrelation.h"
#include "../modelbuilder.h"
#include "../model.h"
#include <QDebug>
#include "../collection.h"
#include <QJsonArray>
HasManyRelation::HasManyRelation(const ModelBuilder &query, const Model &parent, const QString &foreignKey, const QString &localKey, const QString &name) : Relation (query,parent,name),_foreignKey(foreignKey),_localKey(localKey)
{
    if(foreignKey.isNull())
        _foreignKey=QString("%1_%2").arg(Relation::parent().modelName().toLower(),Relation::parent().primaryKey().toString());

    if(localKey.isNull())
        _localKey=Relation::parent().primaryKey().toString();

    if(Relation::parent().exists()){
        Relation::query().where(HasManyRelation::foreignKey(),Relation::parent().get(HasManyRelation::localKey()));
    }
}

HasManyRelation::~HasManyRelation()
{
    //qDebug()<<Q_FUNC_INFO;
}

QString HasManyRelation::foreignKey() const
{
    return _foreignKey;
}

QString HasManyRelation::localKey() const
{
    return _localKey;
}

void HasManyRelation::addConstraints(Collection &models)
{
    QVariantList ids;
    for(const Model &model : models){
        ids << model.get(localKey());
    }

    query().whereIn(foreignKey(),ids);
}

void HasManyRelation::match(Collection &models)
{
    Collection results=get();

    QList< QVariant> pks;
    pks.reserve(results.size());
    for(int i=0; i<results.size(); i++){
        pks << results.at(i)[_foreignKey];
    }

    Collection inserts;
    inserts.reserve(results.size());
    for (Model &mainModel : models){
        const QVariant mainModelPkValue=mainModel.get(_localKey);

        inserts.clear();
        for(int i=0; i<results.size(); i++)
        {
            if(results.isEmpty()){
                mainModel.set(d->m_name,QJsonArray());
                continue;
            }

            if(mainModelPkValue==pks.at(i)){
                inserts << results.at(i);;
            }
        }
        mainModel.set(d->m_name,QJsonArray(inserts));
        //mainModel.setSaved();
    }
}
