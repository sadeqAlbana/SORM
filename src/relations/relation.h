#ifndef RELATION_H
#define RELATION_H
#include "../model.h"
#include "../builder.h"
class Relation
{
public:
    Relation(Model parent, Builder query);
    Collection get();
    protected:
    const Model _parent;
    const Model _related;
    Builder _builder;


};

#endif // RELATION_H
