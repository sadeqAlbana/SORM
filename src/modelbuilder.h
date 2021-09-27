#ifndef MODELBUILDER_H
#define MODELBUILDER_H
#include "builder.h"
class Model;
class Collection;
#include "primarykey.h"
#include "relations/relationlist.h"
class ModelBuilder
{
public:
    ModelBuilder(const Model &model);
    ModelBuilder(const ModelBuilder &other);
    ~ModelBuilder();
    ModelBuilder(const QString &table, const PrimaryKey &primaryKey,const QString &modelName,const bool &usesTimestamps,const bool &usesAutoIncrement);
//    ModelBuilder(const ModelBuilder &other);
    Model model() const;
    Collection get(const QVariant &column=QVariant());
    ModelBuilder &where(QString key, QVariant value);
    ModelBuilder &where(QString key,QString op, QVariant value);
    ModelBuilder &where(QString clause);
    ModelBuilder &whereIn(QString key, QVariantList values);
    ModelBuilder &whereIn(QString key, QString subQuery);
    ModelBuilder &with(const Relation &relation);

    Model first();
    Model find();
    bool insert(Model &mdl);
    bool update(Model &mdl);
    bool remove(Model &model);
    Builder &builder(){return _builder;}
    ModelBuilder &paginate(int page, int count);
    ModelBuilder & take(int l){builder().take(l); return *this;}
    ModelBuilder & select(QStringList args){builder().select(args); return *this;}




private:
    Model *_model;
    Builder _builder;
    RelationList relations;
};

#endif // MODELBUILDER_H
