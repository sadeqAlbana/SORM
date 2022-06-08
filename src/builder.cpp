/*
 * Copyright (C) 2022 Sadeq Albana
 *
 * Licensed under the GNU Lesser General Public License v3.0 :
 * https://www.gnu.org/licenses/lgpl-3.0.html
 */

#include "builder.h"
#include "collection.h"
#include <QDebug>
#include <QSqlRecord>
#include <QDateTime>
#include <QSqlError>
#include <QSqlQuery>
#include "model.h"
#include "db.h"
#ifdef ENABLE_EXCEPTIONS
#include "databaseerrorexception.h"
#endif
Builder::Builder(const QString &table) :
tableClause(table),
  columnsClause("*"),
  _limit(0)
{
    dbDriver=QSqlDatabase::database().driverName();
}

Builder::~Builder()
{
    //qDebug()<<Q_FUNC_INFO;
}

Builder &Builder::where(QString key, QVariant value)
{
    whereClause.append(QString(" %1 %2 = %3").arg(whereClause.size() ? "and" : "where").arg(key).arg(QString("'%1'").arg(value.toString())));
    return *this;
}

Builder &Builder::where(QString key, QString op, QVariant value)
{
    whereClause.append(QString(" %1 %2 %3 %4").arg(whereClause.size() ? "and" : "where").arg(key).arg(op).arg(QString("'%1'").arg(value.toString())));

    return *this;
}

Builder &Builder::orWhere(QString key, QVariant value)
{
    whereClause.append(QString(" %1 %2 = %3").arg(whereClause.size() ? "or" : "where").arg(key).arg(QString("'%1'").arg(value.toString())));
    return *this;
}

Builder &Builder::orWhere(QString key, QString op, QVariant value)
{
    whereClause.append(QString(" %1 %2 %3 %4").arg(whereClause.size() ? "or" : "where").arg(key).arg(op).arg(QString("'%1'").arg(value.toString())));

    return *this;
}

Builder &Builder::whereRaw(QString clause)
{

    whereClause.append(QString(" %1 %2").arg(whereClause.size() ? "and" : "where").arg(clause));

    return *this;
}

Builder &Builder::orWhereRaw(QString clause)
{
    whereClause.append(QString(" %1 %2").arg(whereClause.size() ? "or" : "where").arg(clause));

    return *this;
}




Builder &Builder::whereIn(QString key, QVariantList values)
{

    QString valuesString;
    for (const QVariant &value : values) {
        if(value.type()==QMetaType::Int || value.type()==QMetaType::Double || value.type()==QMetaType::Float || value.type()==QMetaType::Long
                || value.type()==QMetaType::LongLong || value.type()==QMetaType::UInt || value.type()==QMetaType::UShort)
            valuesString.append(value.toString()+",");
        else{
            valuesString.append("'"+value.toString()+"'"+",");

        }
    }
    valuesString.chop(1);

    whereClause.append(QString(" %1 %2 in ( %3 )").arg(whereClause.size() ? "and" : "where").arg(key).arg(valuesString));


    return *this;
}

Builder &Builder::orWhereIn(QString key, QVariantList values)
{
    QString valuesString;
    for (const QVariant &value : values) {
        if(value.type()==QMetaType::Int || value.type()==QMetaType::Double || value.type()==QMetaType::Float || value.type()==QMetaType::Long
                || value.type()==QMetaType::LongLong || value.type()==QMetaType::UInt || value.type()==QMetaType::UShort)
            valuesString.append(value.toString()+",");
        else{
            valuesString.append("'"+value.toString()+"'"+",");

        }
    }
    valuesString.chop(1);

    whereClause.append(QString(" %1 %2 in ( %3 )").arg(whereClause.size() ? "or" : "where").arg(key).arg(valuesString));


    return *this;
}

Builder &Builder::whereIn(QString key, QString subQuery)
{
    whereClause.append(QString(" %1 %2 in ( %3 )").arg(whereClause.size() ? "and" : "where").arg(key).arg(subQuery));

    return *this;
}

Builder &Builder::orWhereIn(QString key, QString subQuery)
{
    whereClause.append(QString(" %1 %2 in ( %3 )").arg(whereClause.size() ? "or" : "where").arg(key).arg(subQuery));

    return *this;
}

Builder &Builder::groupBy(QString column)
{
    groupByClause=column;
    return *this;
}

Builder &Builder::orderBy(QString column)
{
    orderByClause=column;
    return *this;
}

Builder &Builder::skip(int offset)
{
    this->offset = offset;
    return *this;
}

Builder &Builder::simplePaginate(int page, int count)
{
    if(!(page==1))
        skip(page*count);
    take(count);
    return *this;
}



Builder &Builder::join(const QString &table, const QString &first, const QString op, const QString &second)
{
    joinClause+=QString(" inner join %1 on %2 %3 %4").arg(escapeTable(table))
            .arg(first)
            .arg(op)
            .arg(second);

    return *this;
}

QSqlQuery Builder::get()
{
    return DB::exec(generateSql());
}

QVariant Builder::sum(const QString &field)
{
    QString statement=QString("select sum(%1) from %2").arg(field).arg(tableClause);
    if(whereClause.size())
        statement.append(whereClause);

    QSqlQuery query= DB::exec(statement);
    query.first();
    return query.value(0);
}

QVariant Builder::max(const QString &field)
{
    QString statement=QString("select max(%1) from %2").arg(field).arg(tableClause);
    if(whereClause.size())
        statement.append(whereClause);

    QSqlQuery query= DB::exec(statement);
    query.first();
    return query.value(0);
}

int Builder::count(const QString &field)
{
    QString statement=QString("select count(%1) from %2").arg(field).arg(tableClause);
    if(whereClause.size())
        statement.append(whereClause);

    QSqlQuery query=DB::exec(statement);
    query.first();
    return query.value(0).toInt();
}

QString Builder::generateSql()
{
// qDebug()<<"Columns: " << columnsClause;
//    qDebug()<<"Table: " << tableClause;
    QString qry=QString("select %1 from %2").arg(columnsClause).arg(tableClause);

    if(joinClause.size())
        qry.append(joinClause);

    if(whereClause.size())
        qry.append(whereClause);
    if(groupByClause.size())
        qry.append(QString(" group by %1").arg(groupByClause));
    if(orderByClause.size())
        qry.append(QString(" order by %1").arg(orderByClause));
    if(_limit){
        if(offset)
            qry.append(QString(" limit %1 offset %2").arg(_limit).arg(offset));
        else{
            qry.append(QString(" limit %1").arg(_limit));

        }
    }
    //qDebug()<<qry;
    return qry;
}

Builder &Builder::select()
{
    if(columnsClause.at(columnsClause.size()-1)==",")
        columnsClause.remove(columnsClause.size()-1,1);
    return *this;
}

Builder &Builder::select(QStringList args)
{
    if(args.size())
    {
        if(columnsClause=="*")
            columnsClause.clear();

        for(int i=0; i<args.size()-1; i++)
            columnsClause.append(QString(" %1,").arg(args.at(i)));
        columnsClause.append(QString(" %1").arg(args.at(args.size()-1)));
    }
    return *this;
}

bool Builder::insert(const QVariantMap &map)
{
    QStringList columns, bindValues;

    for(const QString &key : map.keys())
    {
        columns << escapeKey(key);
        bindValues << QString(":%1").arg(key);
    }


    QString statement=QString("insert into %1 (%2) values(%3);").arg(tableClause).
            arg(columns.join(",")).
            arg(bindValues.join(","));;

    QSqlQuery query=DB::exec(statement,map);

    if(query.lastError().type()==QSqlError::NoError){
        m_lastInsertId=query.lastInsertId();
        return true;
    }

    return false;
}

bool Builder::update(const QVariantMap &map)
{
    QStringList assignments;

    for(const QString &key : map.keys())
        assignments << QString("%1=%2").arg(escapeKey(key)).arg(QString(":%1").arg(key));


    QString statement=QString("update %1 set %2 ").arg(tableClause).arg(assignments.join(","));

    if(!whereClause.isEmpty())
        statement.append(whereClause); //must set bind values too


    QSqlQuery query=DB::exec(statement,map);
    if(query.lastError().type()==QSqlError::NoError)
        return true;

    return false;
}

bool Builder::remove()
{
    QString statement=QString("delete from %1 ").arg(escapeTable());

    if(!whereClause.isEmpty())
        statement.append(whereClause);

    QSqlQuery query= DB::exec(statement);

    if(query.lastError().type()==QSqlError::NoError)
        return true;

    return false;
}

QVariant Builder::lastInsertId() const
{
    return m_lastInsertId;
}

bool Builder::executeQuery(QSqlQuery &query,const QString &statement)
{
    bool success= statement.isNull() ?  query.exec() : query.exec(statement);

//    if(!statement.isNull())
//        qDebug()<<"statement: " << statement;
//    else
//        qDebug()<<"query: " << query.executedQuery();

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
    return success;
}

QString Builder::escapeKey(const QString &key) const
{
    return dbDriver == "QSQLITE" ?
                QString("`%1`").arg(key):
                QString("`%1`.`%2`").arg(tableClause).arg(key);
}

QString Builder::escapeTable(const QString &table) const
{
    return QString ("`%1`").arg(table.isNull() ? tableClause : table);
}
