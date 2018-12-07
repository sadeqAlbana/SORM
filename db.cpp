#include "db.h"

DB::DB()
{

}

Builder DB::table(const QString &table)
{
    Builder builder(table);
}
