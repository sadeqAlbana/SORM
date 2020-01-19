#include "hasmanyrelation.h"
#include "../modelbuilder.h"
#include "../model.h"
HasManyRelation::HasManyRelation(const ModelBuilder &query, const ModelBuilder &parent, const QString &foreignKey, const QString &localKey) : Relation (query,parent,foreignKey,localKey)
{
    if(foreignKey.isNull())
        _foreignKey=QString("%1_%2").arg(Relation::parent().modelName()).arg(Relation::parent().primaryKey());

    if(localKey.isNull())
        _localKey=Relation::parent().primaryKey();

    _query.where(Relation::foreignKey(),Relation::parent().get(localKey));
}
