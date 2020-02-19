#ifndef MODEL_H
#define MODEL_H
#include <QString>
#include <QVariant>
class HasManyRelation;
class hasManyThroughRelation;
class HasOneThroughRelation;
class HasOneRelation;
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

      template<class T,class B>
      hasManyThroughRelation hasManyThrough(                           const QString &firstKey=QString(),
                                                                       const QString &secondKey=QString(),
                                                                       const QString &localKey=QString(),
                                                                       const QString &secondLocalKey=QString());

      template<class T,class B>
      HasOneThroughRelation hasOneThrough(                           const QString &firstKey=QString(),
                                                                       const QString &secondKey=QString(),
                                                                       const QString &localKey=QString(),
                                                                      const QString &secondLocalKey=QString());
};


#include "modelbuilder.h"
#include "relations/relation.h"
#include "relations/hasmanyrelation.h"
#include "relations/hasmanythroughrelation.h"
#include "relations/hasonethroughrelation.h"
#include "relations/hasonerelation.h"
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
template<class T,class B>
hasManyThroughRelation Model::hasManyThrough( const QString &firstKey,
                                              const QString &secondKey,
                                              const QString &localKey,
                                              const QString &secondLocalKey)
{
    return hasManyThroughRelation(T::staticBuilder(),*this,B(),firstKey,secondKey,localKey,secondLocalKey);
}

template<class T,class B>
HasOneThroughRelation Model::hasOneThrough( const QString &firstKey,
                                              const QString &secondKey,
                                              const QString &localKey,
                                              const QString &secondLocalKey)
{
    return HasOneThroughRelation(T::staticBuilder(),*this,B(),firstKey,secondKey,localKey,secondLocalKey);
}

#include "eloquentmodel.h"
#endif // MODEL_H
