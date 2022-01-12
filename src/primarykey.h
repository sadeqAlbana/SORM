/*
 * Copyright (C) 2022 Sadeq Albana
 *
 * Licensed under the GNU Lesser General Public License v3.0 :
 * https://www.gnu.org/licenses/lgpl-3.0.html
 */

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
