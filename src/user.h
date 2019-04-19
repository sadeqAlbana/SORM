#ifndef USER_H
#define USER_H
#include "model.h"

class User : public Model
{
public:
    ELOQUENT_MODEL(User, users, id)
};

#endif // USER_H
