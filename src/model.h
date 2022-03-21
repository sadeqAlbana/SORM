/*
 * Copyright (C) 2022 Sadeq Albana
 *
 * Licensed under the GNU Lesser General Public License v3.0 :
 * https://www.gnu.org/licenses/lgpl-3.0.html
 */

#ifndef MODEL_H
#define MODEL_H
#include <QString>
#include <QVariant>
#include "primarykey.h"
class HasManyRelation;
class HasOneRelation;
class BelongsToRelation;
class BelongsToManyRelation;
class ModelBuilder;
class Relation;
class RelationList;
class Model  //consider using the Q_GADGET macro for furuture improvments !
{
    friend class ModelBuilder;
    friend class Relation;
public:
    Model(const QString &table=QString(), const PrimaryKey &primarykey=QString(),const QString &modelName=QString(),bool usesTimeStamps=true,bool usesIncrementing=true);

    //Model(const QMap<QString, QVariant> &map);
    ~Model();
    void set(QString key, QVariant value);
    QVariant get(QString key) const;
    QStringList keys() const {return data.keys();}
    QStringList dirtyKeys() const;
    QDateTime created_at() const;
    QDateTime updated_at() const;
    bool exists() const{return _exists;}
    bool usesTimestamps() const;
    void setUseTimestamps(bool use=true){_useTimeStamps=use;}
    bool incrementing() const {return _incrementing;}
    QVariant operator[](const QString key);
    QString table()const {return _table;}
    PrimaryKey primaryKey() const {return _primaryKey;}
    QString modelName() const {return _modelName;}
    ModelBuilder builder() const;
    bool save();
    bool remove();

    operator QJsonObject() const;
    operator QJsonValue() const;


    operator QVariant() const;

protected:
    bool _exists;
    void setSaved();
    QMap<QString, QVariant> data;
    QMap<QString, QVariant> original;
    QString _table;
    PrimaryKey _primaryKey;
    QString _modelName;
    bool _useTimeStamps;
    bool _incrementing;

public:
      template<class T>
      HasManyRelation hasMany(QString foreignKey=QString(),
                         QString localKey=QString(), QString name=QString()) const;

      template<class T>
      HasManyRelation hasMany(QString foreignKey,
                         QString localKey,const Relation &rel, QString name=QString()) const;
      template<class T>
      HasManyRelation hasMany(QString foreignKey,
                         QString localKey,const RelationList &relations, QString name=QString()) const;

      template<class T>
      HasOneRelation hasOne(QString foreignKey=QString(),
                         QString localKey=QString()) const;

      template<class T>
      HasOneRelation hasOne(QString foreignKey,
                         QString localKey,const Relation &rel) const;

      template<class T>
      HasOneRelation hasOne(QString foreignKey,
                         QString localKey, const QString name) const;

      template<class T>
      HasOneRelation hasOne(QString foreignKey,
                         QString localKey, const Relation &relation, QString name=QString()) const;

      template<class T>
      HasOneRelation hasOne(QString foreignKey,
                         QString localKey, const RelationList &relations, QString name=QString()) const;



      template<class T>
      BelongsToManyRelation belongsToMany(                          const QString &table,
                                                                    const QString &foreignPivotKey=QString(),
                                                                    const QString &relatedPivotKey=QString(),
                                                                    const QString &parentKey=QString(),
                                                                    const QString &relatedKey=QString(),
                                                                    const QString &name=QString()) const;


      template<class T>
      BelongsToRelation belongsTo(QString foreignKey=QString(),
                                  QString ownerKey=QString()) const;
};













#include "modelbuilder.h"
#include "relations/relation.h"
#include "relations/relationlist.h"
#include "relations/hasmanyrelation.h"
#include "relations/hasonerelation.h"
#include "relations/belongstomanyrelation.h"
#include "relations/belongstorelation.h"
template<class T>
HasManyRelation Model::hasMany(QString foreignKey, QString localKey,QString name) const
{


    return HasManyRelation(T::staticBuilder(),*this,foreignKey,localKey,name);
}

template<class T>
HasManyRelation Model::hasMany(QString foreignKey, QString localKey, const Relation &rel, QString name) const
{
    return HasManyRelation(T::with(rel),*this,foreignKey,localKey,name);
}

template<class T>
        HasManyRelation Model::hasMany(QString foreignKey, QString localKey, const RelationList &relations, QString name) const
{
     return HasManyRelation(T::with(relations),*this,foreignKey,localKey,name);
}



template<class T>
HasOneRelation Model::hasOne(QString foreignKey,QString localKey) const
{
    return HasOneRelation(T::staticBuilder(),*this,foreignKey,localKey);
}

template<class T>
HasOneRelation Model::hasOne(QString foreignKey,QString localKey,const Relation &rel) const
{
    return HasOneRelation(T::with(rel),*this,foreignKey,localKey);
}


template<class T>
BelongsToManyRelation Model::belongsToMany(const QString &table, const QString &foreignPivotKey, const QString &relatedPivotKey, const QString &parentKey, const QString &relatedKey, const QString &name) const
{
    return BelongsToManyRelation(T::staticBuilder(),*this,table,foreignPivotKey,relatedPivotKey,parentKey,relatedKey,name);
}

template<class T>
BelongsToRelation Model::belongsTo(QString foreignKey, QString ownerKey) const
{
    return BelongsToRelation(T::staticBuilder(),*this,foreignKey,ownerKey);
}

template<class T>
       HasOneRelation Model::hasOne(QString foreignKey, QString localKey, const QString name) const
{
           return HasOneRelation(T::staticBuilder(),*this,foreignKey,localKey,name);
}

template<class T>
       HasOneRelation Model::hasOne(QString foreignKey, QString localKey, const Relation &relation, QString name) const
{
           return HasOneRelation(T::with(relation),*this,foreignKey,localKey,name);
}

template<class T>
       HasOneRelation Model::hasOne(QString foreignKey, QString localKey, const RelationList &relations, QString name) const
{
           return HasOneRelation(T::with(relations),*this,foreignKey,localKey,name);
}


#include "eloquentmodel.h"
#endif // MODEL_H
