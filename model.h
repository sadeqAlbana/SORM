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


//    static Collection all();
//    static Model find(const QVariant &id);
//    static Collection where(const QString &key, const QVariant &value);

    //virtual QString table() const {return QString();}

    QDateTime created_at();
    QDateTime updated_at();

    bool exists(){return _exists;}
    bool usesTimestamps();
    //QString _table;
    //QString _primaryKey;

    QVariant operator[](const QString key);

private:
    bool _exists;
    void setSaved();
    QMap<QString, QVariant> data;
    QMap<QString, QVariant> original;






};

#include "eloquentmodel.h"
#endif // MODEL_H
