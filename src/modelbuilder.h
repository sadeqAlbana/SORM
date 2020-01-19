#ifndef MODELBUILDER_H
#define MODELBUILDER_H
#include "builder.h"
class Model;
class Collection;
class Relation;
class ModelBuilder
{
public:
    ModelBuilder(const Model &model);
    ModelBuilder(const QString &table, const QString &primaryKey,const QString &modelName);
    Model model() const;
    Collection get(const QVariant &column=QVariant());
    ModelBuilder &where(QString key, QVariant value);
    ModelBuilder &where(QString key,QString op, QVariant value);
    ModelBuilder &where(QString clause);
    ModelBuilder &with(const Relation &relation);
    Model first();
    Model find();
    bool insert(Model &model);
    bool update(Model &model);
    bool remove(const Model &model);


private:
    Builder &builder(){return _builder;}
    QString _table;
    QString _primaryKey;
    QString _modelName;
    bool    _usesTimestamps;
    QString table() const;
    QString primaryKey() const;
    QString modelName() const;
    bool usesTimestamps() const;
    Builder _builder;
    QList<Relation> relations;
};

#endif // MODELBUILDER_H
