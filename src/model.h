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
    QVariant operator[](const QString key);

protected:
    bool _exists;
    void setSaved();
    QMap<QString, QVariant> data;
    QMap<QString, QVariant> original;
};

#include "eloquentmodel.h"
#endif // MODEL_H
