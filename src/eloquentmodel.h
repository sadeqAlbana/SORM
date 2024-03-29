/*
 * Copyright (C) 2022 Sadeq Albana
 *
 * Licensed under the GNU Lesser General Public License v3.0 :
 * https://www.gnu.org/licenses/lgpl-3.0.html
 */

#ifndef ELOQUENTMODEL_H
#define ELOQUENTMODEL_H
#include <QString>
#include "collection.h"
#define ELOQUENT_MODEL(_class, tableName, _primaryKey, _useTimeStamps,_useAutoIncrement) \
    public: \
    static QString staticTable(){return QString(#tableName);} \
    static PrimaryKey staticPrimaryKey(){return PrimaryKey(_primaryKey);} \
    static QString staticClassName(){return QString(#_class);} \
    static ModelBuilder staticBuilder(){return ModelBuilder(staticTable(),staticPrimaryKey(),staticClassName(),_useTimeStamps,_useAutoIncrement);} \
    _class() : Model(#tableName,staticPrimaryKey(),#_class,_useTimeStamps,_useAutoIncrement){} \
    _class(const Model &model) : Model(model){} \
    static Collection all(const QVariant &column=QVariant()){return staticBuilder().get(column);} \
    static ModelBuilder where(const QString &key, const QVariant &value) \
    {return staticBuilder().where(key,value);} \
    static ModelBuilder where(const QString &key, const QString &op, const QVariant &value) \
    {return staticBuilder().where(key,op,value);} \
    static Model find(const QVariant value){\
    if(staticPrimaryKey().isString())\
        return staticBuilder().where(staticPrimaryKey().toString(),value).get().value(0);\
    else\
        {   \
    ModelBuilder builder = staticBuilder();\
    QVariantList values=value.toList();\
    QStringList keys = staticPrimaryKey().toStringList(); \
    for(int i=0; i<keys.size();i++ ) \
        builder.where(keys.value(i),values.value(i));\
    return builder.get().value(0); \
        }\
    }\
    static ModelBuilder with(const Relation &relation){return staticBuilder().with(relation); } \
    static ModelBuilder with(const RelationList &relations){return staticBuilder().with(relations); } \
    private:
#endif // ELOQUENTMODEL_H
