#ifndef HASMANYRELATION_H
#define HASMANYRELATION_H

#include "relation.h"
class HasManyRelation : public Relation
{
public:
    HasManyRelation(const ModelBuilder &query, const ModelBuilder &parent,const QString &foreignKey=QString(),
                    const QString &localKey=QString());
};

#endif // HASMANYRELATION_H
