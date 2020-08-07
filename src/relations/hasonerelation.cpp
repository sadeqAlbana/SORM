#include "hasonerelation.h"

#include "../modelbuilder.h"
#include "../model.h"
#include <QDebug>
HasOneRelation::HasOneRelation(const ModelBuilder &query, const Model &parent, const QString &foreignKey, const QString &localKey) : Relation (query,parent),_foreignKey(foreignKey),_localKey(localKey)
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
        for (Model &relationModel : results)
        {
            if(mainModel.get(localKey())==relationModel.get(foreignKey())){
                mainModel.set(related().table(),relationModel);
                break;
            }
        }

        //mainModel.setSaved();
    }
}
