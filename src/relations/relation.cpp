#include "relation.h"
#include "../collection.h"
#include "../model.h"
#include <QDebug>
Relation::Relation(const ModelBuilder &query, const Model &parent) :
    _parent(new Model(parent)),
    _query(query)
{

}

Relation::Relation(const Relation &other): _parent(new Model(*other._parent)),_query(other._query)
{

}

Collection Relation::get(const QVariant &columns)
{
    return _query.get(columns);
}

Model Relation::parent()
{
    return *_parent;
}

Model Relation::related()
{
    return query().model();
}


ModelBuilder &Relation::query()
{
    return _query;
}


