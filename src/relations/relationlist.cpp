#include "relationlist.h"
#include "relation.h"
RelationList::RelationList()
{

}

RelationList::RelationList(const RelationList &other)
{
    for (auto ptr : other) {
        append(ptr->clone());
    }
}

RelationList::~RelationList()
{
    qDeleteAll(this->begin(),this->end());
}


