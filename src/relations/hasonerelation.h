/*
 * Copyright (C) 2022 Sadeq Albana
 *
 * Licensed under the GNU Lesser General Public License v3.0 :
 * https://www.gnu.org/licenses/lgpl-3.0.html
 */

#ifndef HASONERELATION_H
#define HASONERELATION_H
#include "relation.h"
class HasOneRelation : public Relation //inverse of belongs to
{
public:
    HasOneRelation(const ModelBuilder &query, const Model &parent, const QString &foreignKey=QString(),
                    const QString &localKey=QString(),const QString &name=QString());
    ~HasOneRelation();
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
