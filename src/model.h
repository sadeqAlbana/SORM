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
#include "modelbuilder.h"

#include "relations/relation.h"
#include "relations/relationlist.h"
#include "relations/hasmanyrelation.h"
#include "relations/hasonerelation.h"
#include "relations/belongstomanyrelation.h"
#include "relations/belongstorelation.h"
class HasManyRelation;
class HasOneRelation;
class BelongsToRelation;
class BelongsToManyRelation;
class ModelBuilder;
class Relation;
class RelationList;

class ModelData : public QSharedData{
public:
    ModelData(const QString &table, const PrimaryKey &primarykey,const QString &modelName,bool usesTimeStamps,bool usesIncrementing):
        _table(table),_modelName(modelName),_useTimeStamps(usesTimeStamps),_incrementing(usesIncrementing),_exists(false),_primaryKey(primarykey)
    {}
    QString _table;
    QString _modelName;
    bool _useTimeStamps;
    bool _incrementing;
    bool _exists;
    PrimaryKey _primaryKey;
    QMap<QString, QVariant> data;
    QMap<QString, QVariant> original;

};

class Model  //consider using the Q_GADGET macro for furuture improvments !
{
    friend class ModelBuilder;
    friend class Relation;
public:
    Model(const QString &table=QString(), const PrimaryKey &primarykey=QString(),const QString &modelName=QString(),bool usesTimeStamps=true,bool usesIncrementing=true);

    //Model(const QMap<QString, QVariant> &map);
    void set(QString key, QVariant value);
    QVariant get(const QString &key) const;
    QStringList keys() const {return d->data.keys();}
    QStringList dirtyKeys() const;
    QDateTime created_at() const;
    QDateTime updated_at() const;
    bool exists() const{return d->_exists;}
    bool usesTimestamps() const;
    void setUseTimestamps(bool use=true){d->_useTimeStamps=use;}
    bool incrementing() const {return d->_incrementing;}
    QVariant  operator[](const QString key) const;
    QVariant& operator[](const QString key);

    QString table()const {return d->_table;}
    PrimaryKey primaryKey() const {return d->_primaryKey;}
    QString modelName() const {return d->_modelName;}
    ModelBuilder builder() const;
    bool save();
    bool remove();

    operator QJsonObject() const;
    operator QJsonValue() const;


    operator QVariant() const;

protected:
    void setSaved();

    QSharedDataPointer<ModelData> d;

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

Q_DECLARE_TYPEINFO(Model, Q_MOVABLE_TYPE);

#endif // MODEL_H
#include "eloquentmodel.h"
