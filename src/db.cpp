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

Builder DB::table(const QString &table)
{
    return Builder(table);
}

QSqlError DB::lastError()
{
    return _lastError;
}

QSqlQuery DB::exec(const QString &statement, const QVariantMap &bindings)
{
    QSqlQuery query;
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


    QSqlError error = query.lastError();
    DB::setLastError(error);

#ifdef ENABLE_EXCEPTIONS
    if(error.type()!=QSqlError::NoError){
        if(!statement.isNull())
            qDebug()<<"statement: " << statement;
        else
            qDebug()<<"query: " << query.executedQuery();
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

void DB::setLastError(const QSqlError &lastError)
{
    _lastError = lastError;
}
