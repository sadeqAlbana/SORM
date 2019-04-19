#ifndef COLLECTION_H
#define COLLECTION_H
#include <QList>
#include "model.h"

class Collection : public QList<Model>
{
public:
    Collection();
    operator bool();
    operator QJsonArray();

};

#endif // COLLECTION_H
