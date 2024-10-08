/*
 * Copyright (C) 2022 Sadeq Albana
 *
 * Licensed under the GNU Lesser General Public License v3.0 :
 * https://www.gnu.org/licenses/lgpl-3.0.html
 */

#ifndef MODELBUILDER_H
#define MODELBUILDER_H

#include "builder.h"
#include "primarykey.h"
#include "relations/relationlist.h"

class Model;
class Collection;

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
    ModelBuilder &orWhere(QString key, QVariant value);
    ModelBuilder &orWhere(QString key,QString op, QVariant value);
    ModelBuilder &whereRaw(QString clause);
    ModelBuilder &whereBetween(QString key, QVariant op1, QVariant op2); //not perfect


    ModelBuilder &orWhereRaw(QString clause);
    ModelBuilder &orWhereBetween(QString key, QVariant op1, QVariant op2); //not perfect

    ModelBuilder &whereIn(QString key, QVariantList values);
    ModelBuilder &whereIn(QString key, QString subQuery);
    ModelBuilder &whereNotIn(QString key, QVariantList values);
    ModelBuilder &whereNotIn(QString key, QString subQuery);
    ModelBuilder &with(const Relation &relation);
    ModelBuilder &with(const RelationList &relations);
    ModelBuilder &groupBy(QString column);
    ModelBuilder &orderBy(QString column,const QString &direction=QStringLiteral("asc"));
    Model first();
    bool insert(Model &mdl);
    bool update(Model &mdl);
    bool update(QVariantMap map);

    bool remove(Model &model);
    Builder &builder(){return _builder;}
    ModelBuilder &simplePaginate(int page, int count);
    ModelBuilder &paginate(int page, int count);

    ModelBuilder & take(int l){builder().take(l); return *this;}
    ModelBuilder & select(QStringList args){builder().select(args); return *this;}
    ModelBuilder &pluck(const QString &column);
    ModelBuilder &pluck(const QStringList &columns);

private:
    Model *_model;
    Builder _builder;
    RelationList relations;
    int m_count=-1;
    int m_page=-1;
    QStringList m_pluckList;

};

#endif // MODELBUILDER_H
