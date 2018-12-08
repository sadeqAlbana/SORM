#ifndef COLLECTION_H
#define COLLECTION_H
#include <QList>
#include "model.h"

class Collection : public QList<Model>
{
public:
    Collection();
    operator bool();
};

#endif // COLLECTION_H
