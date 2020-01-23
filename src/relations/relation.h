#ifndef RELATION_H
#define RELATION_H
#include "../modelbuilder.h"
class Relation
{
public:
    Relation(const ModelBuilder &query, const Model &parent);
    Collection get();

    Model parent() const;
    Model related() const;
    const ModelBuilder& query() const;

protected:
    Model *_parent;
    ModelBuilder _query;


};

#endif // RELATION_H
