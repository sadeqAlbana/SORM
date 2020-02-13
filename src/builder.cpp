#include "builder.h"
#include "collection.h"
#include <QDebug>
#include <QSqlRecord>
#include <QDateTime>
#include <QSqlError>
#include <QSqlQuery>
#include "model.h"

Builder::Builder(const QString &table) :
tableClause(table),
  columnsClause("*"),
  _limit(0)
{
    dbDriver=QSqlDatabase::database().driverName();
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

Builder &Builder::where(QString clause)
{

    //whereClause="+"+clause+"+";

    return *this;
}

Builder &Builder::whereIn(QString key, QVariantList values)
{

    QString valuesString;
    for (QVariant value : values) {
        valuesString.append(value.toString()+",");
    }
    valuesString.chop(1);

    whereClause.append(QString(" %1 %2 in ( %3 )").arg(whereClause.size() ? "and" : "where").arg(key).arg(valuesString));


    return *this;
}

Builder &Builder::whereIn(QString key, QString subQuery)
{
    whereClause.append(QString(" %1 %2 in ( %3 )").arg(whereClause.size() ? "and" : "where").arg(key).arg(subQuery));

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

Builder &Builder::paginate(int page, int count)
{
    if(!(page==1))
        skip(page*count);
    take(count);
    return *this;
}

Builder &Builder::join(const QString &table, const QString &first, const QString op, const QString &second)
{
    joinClause=QString(" inner join %1 on %2 %3 %4").arg(escapeTable(table))
            .arg(escapeKey(first))
            .arg(op)
            .arg(second);

    return *this;
}




QSqlQuery Builder::get()
{
    QSqlQuery query(generateSql());
    query.exec();
    return query;
}

QSqlQuery Builder::sum(const QString field)
{
    QString qry=QString("select sum(%1) from %2").arg(field).arg(tableClause);
    if(whereClause.size())
        qry.append(whereClause);
    if(_limit)
        qry.append(QString(" limit %1").arg(_limit));

    QSqlQuery query(qry);
    query.exec();

    return query;
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
    if(_limit)
        qry.append(QString(" limit %1").arg(_limit));
    qDebug()<<qry;
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

bool Builder::insert(const Map &map)
{

    QStringList columns, bindValues;

    for(const QString &key : map.keys())
    {
        columns << escapeKey(key);
        bindValues << QString(":%1").arg(key);
    }

    QSqlQuery qry;
    QString qryStr=QString("insert into %1 (%2) values(%3);").arg(tableClause).
            arg(columns.join(",")).
            arg(bindValues.join(","));;


    qry.prepare(qryStr);
    for(const QString &key : map.keys())
    {
        qry.bindValue(QString(":%1").arg(key),map[key]);
    }

    bool result= qry.exec();
    return result;
}

bool Builder::update(const Map &map)
{
    QStringList assignments;

    for(const QString &key : map.keys())
        assignments << QString("%1=%2").arg(escapeKey(key)).arg(QString(":%1").arg(key));

    QSqlQuery qry;
    QString qryStr=QString("update %1 set %2 ").arg(tableClause).arg(assignments.join(","));

    if(!whereClause.isEmpty())
        qryStr.append(whereClause);
    qry.prepare(qryStr);
    for(const QString &key : map.keys())
    {
        qry.bindValue(QString(":%1").arg(key),map[key]);
    }

    return qry.exec();
}

bool Builder::remove()
{
    QString qryStr=QString("delete from %1 ").arg(escapeTable());

    if(!whereClause.isEmpty())
        qryStr.append(whereClause);

    QSqlQuery qry;
    return qry.exec(qryStr);
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
