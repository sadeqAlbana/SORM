#include "relation.h"
#include "../collection.h"
#include "../model.h"
Relation::Relation(const ModelBuilder &query, const Model &parent) :
    _parent(new Model(parent)),
    _query(query)
{

}

Collection Relation::get()
{
    return _query.get();
}

Model Relation::parent() const
{
    return *_parent;
}

Model Relation::related() const
{
    return query().model();
}

const ModelBuilder &Relation::query() const
{
    return _query;
}


