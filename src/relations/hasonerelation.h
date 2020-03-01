#ifndef HASONERELATION_H
#define HASONERELATION_H
#include "relation.h"
class HasOneRelation : public Relation //inverse of belongs to
{
public:
    HasOneRelation(const ModelBuilder &query, const Model &parent, const QString &foreignKey=QString(),
                    const QString &localKey=QString());
    EloquentRelation(HasOneRelation)

    QString foreignKey() const;
    QString localKey() const;
    virtual void addConstraints(Collection &models) override;
    virtual void match(Collection &models) override;



protected:
    QString _foreignKey;
    QString _localKey;
};
#endif // HASONERELATION_H
