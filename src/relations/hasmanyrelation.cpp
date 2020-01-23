#include "hasmanyrelation.h"
#include "../modelbuilder.h"
#include "../model.h"
HasManyRelation::HasManyRelation(const ModelBuilder &query, const Model &parent, const QString &foreignKey, const QString &localKey) : Relation (query,parent)
{
    if(foreignKey.isNull())
        _foreignKey=QString("%1_%2").arg(Relation::parent().modelName().toLower()).arg(Relation::parent().primaryKey());

    if(localKey.isNull())
        _localKey=Relation::parent().primaryKey();
}

QString HasManyRelation::foreignKey() const
{
    return _foreignKey;
}

QString HasManyRelation::localKey() const
{
    return _localKey;
}
