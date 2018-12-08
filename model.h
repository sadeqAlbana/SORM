#ifndef MODEL_H
#define MODEL_H
#include <QString>
#include <QVariant>
#include "builder.h"
class Collection;
class Model
{
public:
    Model();
    void set(QString key, QVariant value);
    QVariant get(QString key);
    bool save();

    static Collection all();
    static Model find(const QVariant &id);
    static Collection where(const QString &key, const QVariant &value);

    virtual QString table() const {return QString();}

    QDateTime created_at();
    QDateTime updated_at();

    bool exists(){return _exists;}

    QString _table;
    QString _primaryKey;
    QMap<QString, QVariant> data;
    bool _exists;


};

#endif // MODEL_H
