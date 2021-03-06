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
HasManyRelation::HasManyRelation(const ModelBuilder &query, const Model &parent, const QString &foreignKey, const QString &localKey, const QString &name) : Relation (query,parent,name),_foreignKey(foreignKey),_localKey(localKey)
{
    if(foreignKey.isNull())
        _foreignKey=QString("%1_%2").arg(Relation::parent().modelName().toLower()).arg(Relation::parent().primaryKey().toString());

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
    for (Model &mainModel : models){
        Collection inserts;
        for (Model &relationModel : results)
        {
            if(results.isEmpty()){
                mainModel.set(m_name,QJsonArray());
                continue;
            }

            if(mainModel.get(localKey())==relationModel.get(foreignKey())){
                inserts << relationModel;
            }
        }
        mainModel.set(m_name,inserts);
        //mainModel.setSaved();
    }
}
