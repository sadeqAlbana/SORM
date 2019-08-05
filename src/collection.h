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
};
QDebug operator <<(QDebug dbg, const Collection &collection);

#endif // COLLECTION_H
