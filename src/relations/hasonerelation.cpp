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
HasOneRelation::HasOneRelation(const ModelBuilder &query, const Model &parent, const QString &foreignKey, const QString &localKey, const QString &name) : Relation (query,parent,name),_foreignKey(foreignKey),_localKey(localKey)
{
    if(foreignKey.isNull())
        _foreignKey=QString("%1_%2").arg(Relation::parent().modelName().toLower()).arg(Relation::parent().primaryKey().toString());

    if(localKey.isNull())
        _localKey=Relation::parent().primaryKey().toString();

    if(Relation::parent().exists()){
        Relation::query().where(HasOneRelation::foreignKey(),Relation::parent().get(HasOneRelation::localKey()));
    }
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

    for (Model &mainModel : models){
        if(results.isEmpty()){
            mainModel.set(m_name,Model());
            break;
        }

        for (Model &relationModel : results)
        {
            if(mainModel.get(localKey())==relationModel.get(foreignKey())){
                mainModel.set(m_name,relationModel);
                break;
            }
        }

        //mainModel.setSaved();
    }
}
