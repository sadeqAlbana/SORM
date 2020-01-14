#ifndef MODEL_H
#define MODEL_H
#include <QString>
#include <QVariant>
class Builder;
class Collection;
class Model
{
    friend class Builder;
public:
    Model();
    Model(const QMap<QString, QVariant> &map);
    ~Model();
    void set(QString key, QVariant value);
    QVariant get(QString key) const;
    QStringList keys() const {return data.keys();}
    QStringList dirtyKeys() const;
    QDateTime created_at();
    QDateTime updated_at();
    bool exists(){return _exists;}
    bool usesTimestamps();
    void setUseTimestamps(bool use=true){_useTimeStamps=use;}
    QVariant operator[](const QString key);
    QString getTable(){return _table;}
    QString getPrimaryKey(){return _primaryKey;}
    QString getModelName(){return _modelName;}

protected:
    bool _exists;
    void setSaved();
    QMap<QString, QVariant> data;
    QMap<QString, QVariant> original;
    bool _useTimeStamps;
//    const QString _table;
//    const QString _primaryKey;
//    const QString _modelName;
      QString _table;
      QString _primaryKey;
      QString _modelName;

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
        foreignKey=QString("%1_%2").arg(getModelName()).arg(getPrimaryKey());

    if(localKey.isEmpty())
        localKey=getPrimaryKey();

    qDebug()<<foreignKey;
    qDebug()<<localKey;


    return T::builder().where(foreignKey,get(localKey)).get();
}

#include "eloquentmodel.h"
#endif // MODEL_H
