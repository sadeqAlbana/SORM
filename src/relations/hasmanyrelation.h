#ifndef HASMANYRELATION_H
#define HASMANYRELATION_H

#include "relation.h"
class HasManyRelation : public Relation
{
public:
    HasManyRelation(const ModelBuilder &query, const Model &parent, const QString &foreignKey=QString(),
                    const QString &localKey=QString());
    EloquentRelation(HasManyRelation)

    QString foreignKey() const;
    QString localKey() const;
    virtual void addConstraints(Collection &models) override;
    virtual void match(Collection &models) override;



protected:
    QString _foreignKey;
    QString _localKey;
};



#endif // HASMANYRELATION_H
