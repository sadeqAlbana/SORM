#include "collection.h"

Collection::Collection()
{

}

Collection::operator bool()
{
    return !!size();
}
