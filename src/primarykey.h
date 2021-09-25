#ifndef PRIMARYKEY_H
#define PRIMARYKEY_H
#include <QStringList>
#include <QString>
class PrimaryKey
{
public:
    PrimaryKey(const QString &str);
    PrimaryKey(const QStringList &list);


    //operator QString();
    //operator QStringList();
    bool isEmpty() const;

    bool isString() const;
    bool isList() const;

    QString toString();
    QStringList toStringList();



private:
    QStringList _list;

};


#endif // PRIMARYKEY_H
