/*
 * Copyright (C) 2022 Sadeq Albana
 *
 * Licensed under the GNU Lesser General Public License v3.0 :
 * https://www.gnu.org/licenses/lgpl-3.0.html
 */

#ifndef DB_H
#define DB_H
class Builder;
class QString;

#include <QSqlError>
#include <QSqlQuery>
#include <QVariantMap>
#include <QThread>

#define CurrentThreadString QString::number(qintptr(QThread::currentThread()))

class DB
{
public:
    DB();

    static Builder table(const QString &table);


    static QSqlError lastError();

    static QSqlQuery exec(const QString &statement, const QVariantMap &bindings=QVariantMap(), const QString connection=QString());
    static QJsonArray select(const QString &statement, const QVariantMap &bindings=QVariantMap());

    //static QVariant lastInsertId();
    static QJsonArray toArray(QSqlQuery &query);
    static bool transaction(const QString &connection=QString());
    static QSqlDatabase database(const QString &connection=QString());
    static bool commit(const QString &connection=QString());

private:
    friend class Builder;
    static void setLastError(const QSqlError &lastError);
    static QSqlError _lastError;
    static QVariant m_lastInsertId;


};

#endif // DB_H
