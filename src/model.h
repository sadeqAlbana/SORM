#ifndef MODEL_H
#define MODEL_H
#include <QString>
#include <QVariant>
class Collection;
class Model
{
    friend class ModelBuilder;
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
      Collection hasMany(QString foreignKey=QString(),
                         QString localKey=QString());
};
#include "collection.h"
#include "builder.h"
#include <QDebug>
template<class T>
Collection Model::hasMany(QString foreignKey,QString localKey)
{
    if(foreignKey.isEmpty())
        foreignKey=QString("%1_%2").arg(modelName()).arg(primaryKey());

    if(localKey.isEmpty())
        localKey=primaryKey();

    return T::builder().where(foreignKey,get(localKey)).get();
}

#include "eloquentmodel.h"
#endif // MODEL_H
