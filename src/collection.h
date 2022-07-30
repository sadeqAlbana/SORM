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
    ~Collection();
    operator bool();
    operator QJsonArray();
    operator QVariant();
    operator QJsonValue();
    operator QJsonObject();

    QVariantList primaryKeys() const;

    int page() const;
    void setPage(int newPage);

    int lastPage() const;
    void setLastPage(int newLastPage);

private:
    int m_page=-1;
    int m_lastPage=-1;
};
QDebug operator <<(QDebug dbg, const Collection &collection);

#endif // COLLECTION_H
