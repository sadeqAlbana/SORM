/*
 * Copyright (C) 2022 Sadeq Albana
 *
 * Licensed under the GNU Lesser General Public License v3.0 :
 * https://www.gnu.org/licenses/lgpl-3.0.html
 */

#ifndef BELONGSTOMANYRELATION_H
#define BELONGSTOMANYRELATION_H
#include "relation.h"

class BelongsToManyRelation : public Relation //requires third table, replace hasManyThrough with this relation
{
public:
    BelongsToManyRelation(const ModelBuilder &query,
                          const Model &parent,
                          const QString &table,
                          const QString &foreignPivotKey=QString(),
                          const QString &relatedPivotKey=QString(),
                          const QString &parentKey=QString(),
                          const QString &relatedKey=QString(),
                          const QString &name=QString());
    EloquentRelation(BelongsToManyRelation)
    virtual void addConstraints(Collection &models) override;
    virtual void match(Collection &models) override;


private:
    QString _table;
    QString _foreignPivotKey;
    QString _relatedPivotKey;
    QString _parentKey;
    QString _relatedKey;
};

#endif // BELONGSTOMANYRELATION_H
