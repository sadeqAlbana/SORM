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
        _foreignKey=QString("%1_%2").arg(Relation::parent().modelName().toLower()).arg(Relation::parent().primaryKey());

    if(ownerKey.isNull())
        _ownerKey=Relation::query().model().primaryKey();

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
        for (Model &relationModel : results)
        {
            if(mainModel.get(foreignKey())==relationModel.get(ownerKey())){
                mainModel.set(related().table(),relationModel);
                break;
            }
        }

        //mainModel.setSaved();
    }
}
