/*
 * Copyright (C) 2022 Sadeq Albana
 *
 * Licensed under the GNU Lesser General Public License v3.0 :
 * https://www.gnu.org/licenses/lgpl-3.0.html
 */

#ifndef RELATIONLIST_H
#define RELATIONLIST_H
#include <QList>
class Relation;

class RelationList : public QList<Relation *>
{
public:
    RelationList();
    RelationList(const RelationList &other);
    ~RelationList();
};

#endif // RELATIONLIST_H
