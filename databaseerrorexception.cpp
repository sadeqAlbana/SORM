#include "databaseerrorexception.h"
#include <QSqlError>
#include <QDebug>
DatabaseErrorException::DatabaseErrorException(const QString &function, const QSqlError &sqlError) : std::exception(),_function(function),_error(sqlError)
{
}

const char *DatabaseErrorException::what() const noexcept
{
    return QString("%1 : %2").arg(_function).arg(error().text()).toUtf8().constData();
}

