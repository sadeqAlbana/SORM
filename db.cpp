#include "db.h"

DB::DB()
{

}

Builder DB::table(const QString &table)
{
    return Builder(table);
}
