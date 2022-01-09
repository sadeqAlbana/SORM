#include "db.h"
#include "builder.h"
#include <QDebug>
#include <databaseerrorexception.h>
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

void DB::setLastError(const QSqlError &lastError)
{
    _lastError = lastError;
}
