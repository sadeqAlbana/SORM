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


