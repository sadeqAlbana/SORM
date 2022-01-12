/*
 * Copyright (C) 2022 Sadeq Albana
 *
 * Licensed under the GNU Lesser General Public License v3.0 :
 * https://www.gnu.org/licenses/lgpl-3.0.html
 */

#ifndef COLLECTION_H
#define COLLECTION_H
#include <QList>
#include <QJsonArray>
class Model;

class Collection : public QList<Model>
{
public:
    Collection();
    operator bool();
    operator QJsonArray();
    operator QVariant();
    operator QJsonValue();

    QVariantList primaryKeys() const;
};
QDebug operator <<(QDebug dbg, const Collection &collection);

#endif // COLLECTION_H
