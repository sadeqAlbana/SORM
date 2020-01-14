#ifndef ELOQUENTMODEL_H
#define ELOQUENTMODEL_H
#include "QString"
#include "builder.h"
#include "collection.h"
#define ELOQUENT_MODEL(_class, tableName,_primaryKey) \
    public: \
    static QString staticTable(){return #tableName;} \
    static QString staticPrimaryKey(){return #_primaryKey;} \
    static QString staticClassName(){return #_class;} \
    static Builder builder(){return Builder(staticTable());} \
    _class(const Model &model) : Model(model){} \
    static Collection all(){return Builder(staticTable()).get();} \
    static Model find(const QVariant value){return Builder(staticTable()).where(staticPrimaryKey(),value).get().value(0);} \
    template<class T> T hasOne(const QString foreignKey = QString("%1_%2").arg(staticClassName()).arg(staticPrimaryKey()), const QString localKey=staticPrimaryKey())\
    {return T::where(foreignKey,get(localKey)).get().value(0);} \
    template<class T> T belongsTo(const QString foreignKey = QString("%1_%2").arg(staticClassName()).arg(staticPrimaryKey()),const QString localKey=staticPrimaryKey()) \
    {return Builder(T::table()).where(localKey,get(foreignKey)).first();}\
    template<class T> Collection belongsToMany(const QString foreignKey = QString("%1_%2").arg(staticClassName()).arg(staticPrimaryKey()),const QString localKey=staticPrimaryKey()) \
    {return Builder(T::table()).where(localKey,get(foreignKey)).get();}\
    static Builder where(const QString key, const QVariant value) \
    {return Builder(staticTable()).where(key,value);} \
    bool save(){return exists() ? Builder(staticTable()).where(staticPrimaryKey(),get(staticPrimaryKey())).update(*this) : Builder(staticTable()).insert(*this);} \
    bool remove(){_exists=false; \
    return Builder(staticTable()).where(staticPrimaryKey(),get(staticPrimaryKey())).remove();} \
    private:
#endif // ELOQUENTMODEL_H
    //template<class T> static _class with()
