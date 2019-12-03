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

}

Builder &Builder::where(QString key, QVariant value)
{
    if(!whereClause.size())
        whereClause.append(QString(" where %1 = %2").arg(key).arg(QString("'%1'").arg(value.toString())));

    return *this;
}

Builder &Builder::where(QString key, QString op, QVariant value)
{
    if(!whereClause.size())
        whereClause.append(QString(" where %1 %2 %3").arg(key).arg(op).arg(QString("'%1'").arg(value.toString())));

    return *this;
}

Builder &Builder::where(QString clause)
{

    whereClause="+"+clause+"+";

    return *this;
}

Builder &Builder::whereIn(QString key, QVariantList values)
{
    if(!whereClause.size())
    {
        QString valuesString;
        for (QVariant value : values) {
            valuesString.append(value.toString()+",");
        }
        valuesString.chop(1);

        whereClause.append(QString(" where %1 in ( %2 )").arg(key).arg(valuesString));
    }

    return *this;
}

Builder &Builder::whereIn(QString key, QString subQuery)
{
    if(!whereClause.size())
        whereClause.append(QString(" where %1 in ( %2 )").arg(key).arg(subQuery));

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

Model Builder::first()
{
    return take(1).get().value(0);
}


Collection Builder::get()
{
    QSqlQuery query(generateSql());
    if(query.exec())
    {
        Collection collection;
        QSqlRecord record=query.record();
        while (query.next()) {
            Model m;
            for(int i=0; i<record.count(); i++)
            {
                m.set(record.fieldName(i),query.value(i));
                m.setSaved();
            }
            collection << m;

        }
        return collection;
    }
    return Collection();
}

Collection Builder::sum(const QString field)
{
    QString qry=QString("select sum(%1) from %2").arg(field).arg(tableClause);
    if(whereClause.size())
        qry.append(whereClause);
    if(_limit)
        qry.append(QString(" limit %1").arg(_limit));

    QSqlQuery query(qry);
    if(query.exec())
    {
        Collection collection;
        QSqlRecord record=query.record();
        while (query.next()) {
            Model m;
            for(int i=0; i<record.count(); i++)
            {
                m.set(record.fieldName(i),query.value(i));
                m.setSaved();
            }
            collection << m;

        }
        return collection;
    }
    return Collection();
}

QString Builder::generateSql()
{
    QString qry=QString("select %1 from %2").arg(columnsClause).arg(tableClause);

    if(whereClause.size())
        qry.append(whereClause);
    if(groupByClause.size())
        qry.append(QString(" group by %1").arg(groupByClause));
    if(orderByClause.size())
        qry.append(QString(" order by %1").arg(orderByClause));
    if(_limit)
        qry.append(QString(" limit %1").arg(_limit));

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

bool Builder::insert(Model &model)
{
    if(model.usesTimestamps())
    {
        QDateTime now=QDateTime::currentDateTime();
        model.set("created_at",now);
        model.set("updated_at",now);
    }

    QStringList columns, bindValues;

    for(const QString &key : model.keys())
    {
        columns << escapeKey(key);
        bindValues << QString(":%1").arg(key);
    }

    QSqlQuery qry;
    QString qryStr=QString("insert into %1 (%2) values(%3);").arg(tableClause).
            arg(columns.join(",")).
            arg(bindValues.join(","));;


    qry.prepare(qryStr);
    for(const QString &key : model.keys())
    {
        qry.bindValue(QString(":%1").arg(key),model[key]);
    }

    return qry.exec();
}

bool Builder::update(Model &model)
{
    if(model.usesTimestamps())
    {
        QDateTime now=QDateTime::currentDateTime();
        model.set("updated_at",now);
    }


    QStringList assignments;

    for(const QString &key : model.dirtyKeys())
        assignments << QString("%1=%2").arg(escapeKey(key)).arg(QString(":%1").arg(key));

    QSqlQuery qry;
    QString qryStr=QString("update %1 set %2 ").arg(tableClause).arg(assignments.join(","));

    if(!whereClause.isEmpty())
        qryStr.append(whereClause);
    qry.prepare(qryStr);
    for(const QString &key : model.dirtyKeys())
    {
        qry.bindValue(QString(":%1").arg(key),model[key]);
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
    return QString("`%1`.`%2`").arg(tableClause).arg(key);
}

QString Builder::escapeTable() const
{
    return QString ("`%1`").arg(tableClause);
}





