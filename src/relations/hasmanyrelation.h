#ifndef HASMANYRELATION_H
#define HASMANYRELATION_H

#include "relation.h"
class HasManyRelation : public Relation
{
public:
    HasManyRelation(Model parent, Builder query, QString foreignKey=QString(), QString localKey=QString());
};

#endif // HASMANYRELATION_H
