#ifndef DB_H
#define DB_H
#include "builder.h"

class DB
{
public:
    DB();

    static Builder table(const QString &table);

};

#endif // DB_H
