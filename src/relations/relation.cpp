#include "relation.h"

Relation::Relation(Model parent, Builder query) : _parent(parent), builder(query)
{

}

Collection Relation::get()
{
    return builder.get();
}
