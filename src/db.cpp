#include "db.h"
#include "builder.h"
DB::DB()
{

}

Builder DB::table(const QString &table)
{
    return Builder(table);
}
