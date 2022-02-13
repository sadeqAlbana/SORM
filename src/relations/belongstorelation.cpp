/*
 * Copyright (C) 2022 Sadeq Albana
 *
 * Licensed under the GNU Lesser General Public License v3.0 :
 * https://www.gnu.org/licenses/lgpl-3.0.html
 */

#include "belongstorelation.h"

#include "../modelbuilder.h"
#include "../model.h"
#include <QDebug>
BelongsToRelation::BelongsToRelation(const ModelBuilder &query,
                                     const Model &child,
                                     const QString &foreignKey,
                                     const QString &ownerKey) : Relation (query,child),_foreignKey(foreignKey),_ownerKey(ownerKey)
{
    if(foreignKey.isNull())
        _foreignKey=QString("%1_%2").arg(Relation::parent().modelName().toLower()).arg(Relation::parent().primaryKey().toString());

    if(ownerKey.isNull())
        _ownerKey=Relation::query().model().primaryKey().toString();

    if(BelongsToRelation::child().exists()){
        Relation::query().where(BelongsToRelation::ownerKey(),BelongsToRelation::child().get(BelongsToRelation::foreignKey()));
    }
}

QString BelongsToRelation::foreignKey() const
{
    return _foreignKey;
}

QString BelongsToRelation::ownerKey() const
{
    return _ownerKey;
}

Model BelongsToRelation::child()
{
    return parent();
}

void BelongsToRelation::addConstraints(Collection &models)
{
    QVariantList ids;
    for(const Model &model : models){
        ids << model.get(foreignKey());
    }

    query().whereIn(ownerKey(),ids);
}

void BelongsToRelation::match(Collection &models)
{
    Collection results=get();
    for (Model &mainModel : models){
        if(results.isEmpty()){
            mainModel.set(m_name,Model());
            continue;
        }

        for (Model &relationModel : results)
        {
            if(mainModel.get(foreignKey())==relationModel.get(ownerKey())){
                mainModel.set(m_name,relationModel);
                break;
            }
        }

        //mainModel.setSaved();
    }
}
