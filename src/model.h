#ifndef MODEL_H
#define MODEL_H
#include <QString>
#include <QVariant>
#include "primarykey.h"
class HasManyRelation;
class hasManyThroughRelation;
class HasOneThroughRelation;
class HasOneRelation;
class BelongsToRelation;
class BelongsToManyRelation;
class ModelBuilder;
class Relation;
class Model
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

    operator QJsonObject();

    operator QVariant();

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
                         QString localKey=QString()) const;
      template<class T>
      HasOneRelation hasOne(QString foreignKey=QString(),
                         QString localKey=QString()) const;



      template<class T>
      BelongsToManyRelation belongsToMany(                          const QString &table,
                                                                    const QString &foreignPivotKey=QString(),
                                                                    const QString &relatedPivotKey=QString(),
                                                                    const QString &parentKey=QString(),
                                                                    const QString &relatedKey=QString()) const;


      template<class T>
      BelongsToRelation belongsTo(QString foreignKey=QString(),
                               QString ownerKey=QString()) const;
};






#include "modelbuilder.h"
#include "relations/relation.h"
#include "relations/hasmanyrelation.h"
#include "relations/hasmanythroughrelation.h"
#include "relations/hasonethroughrelation.h"
#include "relations/hasonerelation.h"
#include "relations/belongstomanyrelation.h"
#include "relations/belongstorelation.h"
template<class T>
HasManyRelation Model::hasMany(QString foreignKey,QString localKey) const
{
    return HasManyRelation(T::staticBuilder(),*this,foreignKey,localKey);
}
template<class T>
HasOneRelation Model::hasOne(QString foreignKey,QString localKey) const
{
    return HasOneRelation(T::staticBuilder(),*this,foreignKey,localKey);
}


template<class T>
BelongsToManyRelation Model::belongsToMany(const QString &table, const QString &foreignPivotKey, const QString &relatedPivotKey, const QString &parentKey, const QString &relatedKey) const
{
    return BelongsToManyRelation(T::staticBuilder(),*this,table,foreignPivotKey,relatedPivotKey,parentKey,relatedKey);
}

template<class T>
BelongsToRelation Model::belongsTo(QString foreignKey, QString ownerKey) const
{
    return BelongsToRelation(T::staticBuilder(),*this,foreignKey,ownerKey);
}

#include "eloquentmodel.h"
#endif // MODEL_H
