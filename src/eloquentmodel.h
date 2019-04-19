#ifndef ELOQUENTMODEL_H
#define ELOQUENTMODEL_H
#include "QString"
#include "builder.h"
#include "collection.h"
#define ELOQUENT_MODEL(_class, tableName,_primaryKey) \
    public: \
    _class() {} \
    _class(Model model) : Model(model){} \
    static QString table(){return #tableName;} \
    static QString primaryKey(){return #_primaryKey;} \
    static QString className(){return #_class;} \
    static Collection all(){return Builder(table()).get();} \
    static Model find(const QVariant value){return Builder(table()).where(primaryKey(),value).get().value(0);} \
    template<class T> Collection hasMany(const QString foreignKey = QString("%1_%2").arg(className()).arg(primaryKey()), const QString localKey=primaryKey()) \
    {return Builder(T::table()).where(foreignKey,get(localKey)).get();} \
    template<class T> T hasOne(const QString foreignKey = QString("%1_%2").arg(className()).arg(primaryKey()), const QString localKey=primaryKey())\
    {return T::where(foreignKey,get(localKey)).value(0);} \
    static Builder where(const QString key, const QVariant value) \
    {return Builder(table()).where(key,value);} \
    bool save(){return exists() ? Builder(table()).where(primaryKey(),get(primaryKey())).update(*this) : Builder(table()).insert(*this);} \
    bool remove(){_exists=false; \
    return Builder(table()).where(primaryKey(),get(primaryKey())).remove();} \
    private:
#endif // ELOQUENTMODEL_H
