#ifndef DB_H
#define DB_H
class Builder;
class QString;

#include <QSqlError>

class DB
{
public:
    DB();

    static Builder table(const QString &table);


    static QSqlError lastError();


private:
    friend class Builder;
    static void setLastError(const QSqlError &lastError);
    static QSqlError _lastError;

};

#endif // DB_H
