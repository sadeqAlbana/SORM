/*
 * Copyright (C) 2022 Sadeq Albana
 *
 * Licensed under the GNU Lesser General Public License v3.0 :
 * https://www.gnu.org/licenses/lgpl-3.0.html
 */

#include "hasonerelation.h"

#include "../modelbuilder.h"
#include "../model.h"
#include <QDebug>
#include "../collection.h"
#include <QJsonArray>
HasOneRelation::HasOneRelation(const ModelBuilder &query, const Model &parent, const QString &foreignKey, const QString &localKey, const QString &name) : Relation (query,parent,name),_foreignKey(foreignKey),_localKey(localKey)
{
    if(foreignKey.isNull())
        _foreignKey=QString("%1_%2").arg(Relation::parent().modelName().toLower(),Relation::parent().primaryKey().toString());

    if(localKey.isNull())
        _localKey=Relation::parent().primaryKey().toString();

    if(Relation::parent().exists()){
        Relation::query().where(HasOneRelation::foreignKey(),Relation::parent().get(HasOneRelation::localKey()));
    }
}

HasOneRelation::~HasOneRelation()
{
    //qDebug()<<Q_FUNC_INFO;
}

QString HasOneRelation::foreignKey() const
{
    return _foreignKey;
}

QString HasOneRelation::localKey() const
{
    return _localKey;
}

void HasOneRelation::addConstraints(Collection &models)
{
    QVariantList ids;
    for(const Model &model : models){
        QVariant id=model.get(localKey());
        if(!ids.contains(id))
            ids << id;
    }

    query().whereIn(foreignKey(),ids);
}

void HasOneRelation::match(Collection &models)
{
    Collection results=get();
    QList< QVariant> pks;
    pks.reserve(results.size());
    for(int i=0; i<results.size(); i++){
        pks << results.at(i)[_foreignKey];
    }
    for (Model &mainModel : models){
        const QVariant mainModelPkValue=mainModel.get(_localKey);
        if(results.isEmpty()){
            mainModel.set(d->m_name,Model());
            continue;
        }

        for(int i=0; i<results.size(); i++)
        {
            //Model &relationModel
            if(mainModelPkValue==pks.at(i)){
                mainModel.set(d->m_name,results.at(i));
                break;
            }
        }

        //mainModel.setSaved();
    }
}
