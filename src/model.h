#ifndef MODEL_H
#define MODEL_H
#include <QString>
#include <QVariant>
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
    Model(const QString &table=QString(), const QString &primarykey=QString(),const QString &modelName=QString(),bool usesTimeStamps=false);
    //Model(const QMap<QString, QVariant> &map);
    ~Model();
    void set(QString key, QVariant value);
    QVariant get(QString key) const;
    QStringList keys() const {return data.keys();}
    QStringList dirtyKeys() const;
    QDateTime created_at();
    QDateTime updated_at();
    bool exists(){return _exists;}
    bool usesTimestamps() const;
    void setUseTimestamps(bool use=true){_useTimeStamps=use;}
    QVariant operator[](const QString key);
    QString table()const {return _table;}
    QString primaryKey() const {return _primaryKey;}
    QString modelName() const {return _modelName;}
    ModelBuilder builder();
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
    QString _primaryKey;
    QString _modelName;
    bool _useTimeStamps;

public:
      template<class T>
      HasManyRelation hasMany(QString foreignKey=QString(),
                         QString localKey=QString());
      template<class T>
      HasOneRelation hasOne(QString foreignKey=QString(),
                         QString localKey=QString());



      template<class T>
      BelongsToManyRelation belongsToMany(                          const QString &table,
                                                                    const QString &foreignPivotKey=QString(),
                                                                    const QString &relatedPivotKey=QString(),
                                                                    const QString &parentKey=QString(),
                                                                    const QString &relatedKey=QString());


      template<class T>
      BelongsToRelation belongsTo(QString foreignKey=QString(),
                               QString ownerKey=QString());
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
HasManyRelation Model::hasMany(QString foreignKey,QString localKey)
{
    return HasManyRelation(T::staticBuilder(),*this,foreignKey,localKey);
}
template<class T>
HasOneRelation Model::hasOne(QString foreignKey,QString localKey)
{
    return HasOneRelation(T::staticBuilder(),*this,foreignKey,localKey);
}


template<class T>
BelongsToManyRelation Model::belongsToMany(const QString &table, const QString &foreignPivotKey, const QString &relatedPivotKey, const QString &parentKey, const QString &relatedKey)
{
    return BelongsToManyRelation(T::staticBuilder(),*this,table,foreignPivotKey,relatedPivotKey,parentKey,relatedKey);
}

template<class T>
BelongsToRelation Model::belongsTo(QString foreignKey, QString ownerKey)
{
    return BelongsToRelation(T::staticBuilder(),*this,foreignKey,ownerKey);
}

#include "eloquentmodel.h"
#endif // MODEL_H
