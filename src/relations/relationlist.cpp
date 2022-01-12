/*
 * Copyright (C) 2022 Sadeq Albana
 *
 * Licensed under the GNU Lesser General Public License v3.0 :
 * https://www.gnu.org/licenses/lgpl-3.0.html
 */

#include "relationlist.h"
#include "relation.h"
RelationList::RelationList() : QList<Relation *> ()
{

}

RelationList::RelationList(const RelationList &other) : QList<Relation *> ()
{
    for (auto ptr : other) {
        append(ptr->clone());
    }
}

RelationList::~RelationList()
{
    qDeleteAll(this->begin(),this->end());
}


