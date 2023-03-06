#ifndef DATABASEERROREXCEPTION_H
#define DATABASEERROREXCEPTION_H
#include <QSqlError>
#include <exception>
class DatabaseErrorException : public std::exception
{
public:
    DatabaseErrorException(const QString &function,const QSqlError &sqlError);
    ~DatabaseErrorException();
    QSqlError error() const {return _error;}

   virtual const char*
   what() const  noexcept;




private:
    QString _function;
    QSqlError _error;
    QByteArray m_errorStr;

};

#endif // DATABASEERROREXCEPTION_H
