#ifndef RELATION_H
#define RELATION_H
#include "../modelbuilder.h"
class Relation
{
public:
    Relation(const ModelBuilder &query, const ModelBuilder &parentBuilder, const QString &foreignKey=QString(),
             const QString &llocalKey=QString());
    Collection get();
    ModelBuilder _parentBuilder;
    ModelBuilder _query;
    Model parent();
    Model related();
    QString _foreignKey;
    QString _localKey;

    QString localKey() const;
    QString foreignKey() const;
    ModelBuilder _builder;
};

#endif // RELATION_H
