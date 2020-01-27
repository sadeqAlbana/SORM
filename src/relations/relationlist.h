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
