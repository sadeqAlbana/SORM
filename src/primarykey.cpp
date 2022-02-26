/*
 * Copyright (C) 2022 Sadeq Albana
 *
 * Licensed under the GNU Lesser General Public License v3.0 :
 * https://www.gnu.org/licenses/lgpl-3.0.html
 */

#include "primarykey.h"
#include <QDebug>

PrimaryKey::PrimaryKey(const QString &str)
{
    _list << str;
}

PrimaryKey::PrimaryKey(const QStringList &list)
{
    _list=list;
}

PrimaryKey::~PrimaryKey()
{
    //qDebug()<<Q_FUNC_INFO;

}

bool PrimaryKey::isEmpty() const
{
    return _list.isEmpty();
}


bool PrimaryKey::isString() const
{
    return (_list.size() == 1);
}

bool PrimaryKey::isList() const
{
    return (_list.size() > 1);
}

QString PrimaryKey::toString()
{
    return _list.value(0);
}

QStringList PrimaryKey::toStringList()
{
    return _list;
}

//PrimaryKey::operator QStringList()
//{
//    return _list;
//}

//Primarykey::operator QString()
//{
//    return _list.value(0);
//}
