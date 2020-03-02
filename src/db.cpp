#include "db.h"
#include "builder.h"
QSqlError DB::_lastError;

DB::DB()
{

}

Builder DB::table(const QString &table)
{
    return Builder(table);
}

QSqlError DB::lastError()
{
    return _lastError;
}

void DB::setLastError(const QSqlError &lastError)
{
    _lastError = lastError;
}
