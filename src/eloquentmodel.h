#ifndef ELOQUENTMODEL_H
#define ELOQUENTMODEL_H
#include "QString"
#include "collection.h"
#include "modelbuilder.h"
#include "model.h"

#define ELOQUENT_MODEL(_class, tableName, _primaryKey, _useTimeStamps) \
    public: \
    static QString staticTable(){return QString(#tableName);} \
    static QString staticPrimaryKey(){return QString(#_primaryKey);} \
    static QString staticClassName(){return QString(#_class);} \
    static ModelBuilder staticBuilder(){return ModelBuilder(staticTable(),staticPrimaryKey(),staticClassName(),_useTimeStamps);} \
    _class() : Model(#tableName,#_primaryKey,#_class,_useTimeStamps){} \
    _class(const Model &model) : Model(model){} \
    static Collection all(){return staticBuilder().get();} \
    static ModelBuilder where(const QString key, const QVariant value) \
    {return staticBuilder().where(key,value);} \
    static Model find(const QVariant value){return staticBuilder().where(staticPrimaryKey(),value).get().value(0);} \
    template<class T> T hasOne(const QString foreignKey = QString("%1_%2").arg(staticClassName()).arg(staticPrimaryKey()), const QString localKey=staticPrimaryKey())\
    {return T::where(foreignKey,get(localKey)).get().value(0);} \
    bool save(){return exists() ? staticBuilder().update(*this) : staticBuilder().insert(*this);} \
    bool remove(){_exists=false; \
    return staticBuilder().remove(*this);} \
    static ModelBuilder with(const Relation &relation){return staticBuilder().with(relation); } \
    private:
#endif // ELOQUENTMODEL_H
    //template<class T> static _class with()
