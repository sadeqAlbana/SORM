#ifndef MODEL_H
#define MODEL_H
#include <QString>
#include <QVariant>
class Model
{
public:
    Model();
    void set(QString key, QVariant value);
    QVariant get(QString key);
    bool save();

    static QString table(){return _table;}

    QDateTime created_at();
    QDateTime updated_at();



    QString _table;
    QMap<QString, QVariant> data;


};

#endif // MODEL_H
