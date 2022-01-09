#ifndef DB_H
#define DB_H
class Builder;
class QString;

#include <QSqlError>
#include <QSqlQuery>
#include <QVariantMap>
class DB
{
public:
    DB();

    static Builder table(const QString &table);


    static QSqlError lastError();

    static QSqlQuery exec(const QString &statement, const QVariantMap &bindings=QVariantMap());

    //static QVariant lastInsertId();


private:
    friend class Builder;
    static void setLastError(const QSqlError &lastError);
    static QSqlError _lastError;
    static QVariant m_lastInsertId;

};

#endif // DB_H
