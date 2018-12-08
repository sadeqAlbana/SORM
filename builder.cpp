#include "builder.h"
#include "collection.h"
#include <QDebug>
#include <QSqlRecord>
Builder::Builder(const QString &table) :
tableClause(table),
  columnsClause("*"),
  _limit(0)
{

}

Builder &Builder::where(QString key, QVariant value)
{
    if(!whereClause.size())
        whereClause.append(QString(" where %1 = %2").arg(key).arg(value.toString()));

    return *this;
}

Builder &Builder::where(QString clause)
{

    whereClause="+"+clause+"+";

    return *this;
}



Collection Builder::get()
{
    QString qry=QString("select %1 from %2").arg(columnsClause).arg(tableClause);

    if(whereClause.size())
        qry.append(whereClause);
    if(_limit)
        qry.append(QString(" limit %1").arg(_limit));
    qDebug()<<qry;

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
            }
            collection << m;

        }
        return collection;
    }
    return Collection();
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



