/*
 * Copyright (C) 2022 Sadeq Albana
 *
 * Licensed under the GNU Lesser General Public License v3.0 :
 * https://www.gnu.org/licenses/lgpl-3.0.html
 */

#include "db.h"
#include "builder.h"
#include <QDebug>
#include <databaseerrorexception.h>
#include <QJsonArray>
#include <QSqlRecord>
#include <QJsonObject>
QSqlError DB::_lastError;
//QVariant DB::m_lastInsertId;

DB::DB()
{

}

DB::~DB()
{
    //qDebug()<<Q_FUNC_INFO;
}

Builder DB::table(const QString &table)
{
    return Builder(table);
}

QSqlError DB::lastError()
{
    return _lastError;
}

QSqlQuery DB::exec(const QString &statement, const QVariantMap &bindings, const QString connection)
{
    //maybe add a third option to use the default connection?

    QSqlQuery query(DB::database(connection));
    if(bindings.count()){
        query.prepare(statement);
        QStringList keys=bindings.keys();
        for(const QString &key : keys){
            query.bindValue(QString(":%1").arg(key),bindings[key]);
        }
        query.exec();
    }else{
        query.exec(statement);
    }

//    if(!statement.isNull())
//        qDebug()<<"statement: " << statement;
//    else
//        qDebug()<<"query: " << query.executedQuery();


    QSqlError error = query.lastError();
    DB::setLastError(error);
    //query.finish();
#ifdef SORM_ENABLE_EXCEPTIONS
    if(error.type()!=QSqlError::NoError){
//        if(!statement.isNull())
//            qDebug()<<"statement: " << statement;
//        else
//            qDebug()<<"query: " << query.executedQuery();
        qDebug()<<"rollback: "<<DB::database().rollback();
        throw  DatabaseErrorException(Q_FUNC_INFO,error);
    }
#endif



    return query;
}

QJsonArray DB::select(const QString &statement, const QVariantMap &bindings)
{
    QSqlQuery query=exec(statement,bindings);

    return DB::toArray(query);
}

QJsonArray DB::toArray(QSqlQuery &query)
{
    QJsonArray array;
    QSqlRecord record=query.record();
    while (query.next()) {
        QJsonObject object;
        for(int i=0; i<record.count(); i++)
        {
            object[record.fieldName(i)]=query.value(i).toJsonValue();
        }
        array << object;

    }
    return array;
}
/*
 * Hi @Calvev, I had the same problem of the missing transactions feature. The problem was that I used a new version of libmysql.dll which I got from the MySQL connector package, but the server I was connecting to, was an older MySQL 5.1, so their versions did not match. When I downloaded the old 5.1 server package and extracted the libmysql.dll from there, transactions started to work :o)
*/
bool DB::transaction(const QString &connection)
{
    return DB::database(connection).transaction();
}

QSqlDatabase DB::database(const QString &connection)
{
    //should it be QLatin1String(defaultConnection) ?
    return connection.isNull()? QSqlDatabase::database(QThread::currentThread()->property("SORM_DB_CONNECTION_STR").toString())
                              : QSqlDatabase::database(connection);
}

bool DB::commit(const QString &connection)
{
    return DB::database(connection).commit();
}

void DB::setLastError(const QSqlError &lastError)
{
    _lastError = lastError;
}
