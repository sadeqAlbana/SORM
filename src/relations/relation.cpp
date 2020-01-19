#include "relation.h"
#include "../collection.h"
#include "../model.h"
Relation::Relation(const ModelBuilder &query, const ModelBuilder &parentBuilder, const QString &foreignKey, const QString &localKey) :
    _parentBuilder(parentBuilder),
    _query(query),
    _foreignKey(foreignKey),
    _localKey(localKey),
    _builder(parent())
{

}

Collection Relation::get()
{
    return _query.get();
}

Model Relation::parent()
{
    return _parentBuilder.model();
}

Model Relation::related()
{
    return _query.model();
}

QString Relation::foreignKey() const
{
    return _foreignKey;
}

QString Relation::localKey() const
{
    return _localKey;
}
