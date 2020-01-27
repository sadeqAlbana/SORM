#ifndef RELATIONLIST_H
#define RELATIONLIST_H
#include <QList>
#include <QSharedPointer>
class Relation;

class RelationList : public QList<QSharedPointer<Relation>>
{
public:
    RelationList();
    //~RelationList();
};

#endif // RELATIONLIST_H
