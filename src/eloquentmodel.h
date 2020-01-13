#ifndef ELOQUENTMODEL_H
#define ELOQUENTMODEL_H
#include "QString"
#include "builder.h"
#include "collection.h"
#define ELOQUENT_MODEL(_class, tableName,_primaryKey) \
    public: \
    static QString table(){return #tableName;} \
    static QString primaryKey(){return #_primaryKey;} \
    static QString className(){return #_class;} \
    _class(Model model) : Model(){} \
    static Collection all(){return Builder(_class()).get();} \
    static Model find(const QVariant value){return Builder(table()).where(primaryKey(),value).get().value(0);} \
    template<class T> T hasOne(const QString foreignKey = QString("%1_%2").arg(className()).arg(primaryKey()), const QString localKey=primaryKey())\
    {return T::where(foreignKey,get(localKey)).get().value(0);} \
    template<class T> T belongsTo(const QString foreignKey = QString("%1_%2").arg(className()).arg(primaryKey()),const QString localKey=primaryKey()) \
    {return Builder().where(localKey,get(foreignKey)).first();}\
    template<class T> Collection belongsToMany(const QString foreignKey = QString("%1_%2").arg(className()).arg(primaryKey()),const QString localKey=primaryKey()) \
    {return Builder(T::table()).where(localKey,get(foreignKey)).get();}\
    static Builder where(const QString key, const QVariant value) \
    {return Builder(table()).where(key,value);} \
    bool save(){return exists() ? Builder(table()).where(primaryKey(),get(primaryKey())).update(*this) : Builder(table()).insert(*this);} \
    bool remove(){_exists=false; \
    return Builder(table()).where(primaryKey(),get(primaryKey())).remove();} \
    static Builder builder(){return Builder(table(),primaryKey());} \
    static Builder with(){return builder();} \
    template<typename First, typename ... Args> static Builder with(First arg, const Args &...rest) \
        {return with(rest...);} \
    private:
#endif // ELOQUENTMODEL_H
    //template<class T> static _class with()
