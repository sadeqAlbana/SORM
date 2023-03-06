#include "databaseerrorexception.h"
#include <QSqlError>
#include <QDebug>
DatabaseErrorException::DatabaseErrorException(const QString &function, const QSqlError &sqlError) : std::exception(),_function(function),_error(sqlError)
{
    m_errorStr=QString("%1 : %2").arg(_function,error().text()).toUtf8();
}

DatabaseErrorException::~DatabaseErrorException()
{
    //qDebug()<<Q_FUNC_INFO;
}

const char *DatabaseErrorException::what() const noexcept
{
    return m_errorStr.constData();
}

