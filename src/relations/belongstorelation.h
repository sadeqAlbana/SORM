#ifndef BELONGSTORELATION_H
#define BELONGSTORELATION_H
#include "relation.h"
class BelongsToRelation : public Relation //inverse of hasOne
{
public:
    BelongsToRelation(const ModelBuilder &query, const Model &child, const QString &foreignKey=QString(),
                    const QString &ownerKey=QString());
    EloquentRelation(BelongsToRelation)

    QString foreignKey() const;
    QString ownerKey() const;
    Model child();
    virtual void addConstraints(Collection &models) override;
    virtual void match(Collection &models) override;



protected:
    QString _foreignKey;
    QString _ownerKey;
};
#endif // BELONGSTORELATION_H
