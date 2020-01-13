#ifndef MODEL_H
#define MODEL_H
#include <QString>
#include <QVariant>
class Builder;
class Collection;
class HasManyRelation;
class Relation;
class Model
{
    friend class Builder;
public:
    //Model(const Model &other, const QString tbl=QString(), const QString pk=QString());
    Model(const QString tbl=QString(), const QString pk=QString(),const QString modelName="Model");
    Model(const QMap<QString, QVariant> &map, const QString tbl=QString(), const QString pk=QString(), const QString modelName="Model");
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
    operator QJsonObject();
    operator QVariant();
    QString getTable(){return _table;}
    QString getPrimaryKey(){return _primaryKey;}
    QString modelName(){return _modelName;}
    template<class T>
    Relation hasMany(const QString foreignKey=QString(), const QString localKey=QString())
    {
        return HasManyRelation(*this,T::builder(),foreignKey,localKey);
    }


protected:
    bool _exists;
    void setSaved();
    QMap<QString, QVariant> data;
    QMap<QString, QVariant> original;
    bool _useTimeStamps;
    QString _table;
    QString _primaryKey;
    QString _modelName;
};



#include "eloquentmodel.h"
#endif // MODEL_H
