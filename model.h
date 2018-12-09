#ifndef MODEL_H
#define MODEL_H
#include <QString>
#include <QVariant>
class Builder;
class Collection;
class Model
{
public:
    Model();
    void set(QString key, QVariant value);
    QVariant get(QString key) const;
    bool save();
    QStringList keys(){return data.keys();}
//    static Collection all();
//    static Model find(const QVariant &id);
//    static Collection where(const QString &key, const QVariant &value);

    virtual QString table() const {return QString();}

    QDateTime created_at();
    QDateTime updated_at();

    bool exists(){return _exists;}

    QString _table;
    QString _primaryKey;
    QMap<QString, QVariant> data;
    bool _exists;

    bool usesTimestamps();


};

#endif // MODEL_H
