#include "builder.h"
#include "collection.h"
#include <QDebug>
#include <QSqlRecord>
Builder::Builder(const QString &table) :
_table(table),
  _columns("*"),
  _limit(0)
{

}

Builder &Builder::where(QString key, QVariant value)
{
    if(!_where.size())
        _where.append(QString(" where %1 = %2").arg(key).arg(value.toString()));

    return *this;
}

Builder &Builder::where(QString clause)
{

    _where="+"+clause+"+";

    return *this;
}



Collection Builder::get()
{
    QString qry=QString("select %1 from %2").arg(_columns).arg(_table);

    if(_where.size())
        qry.append(_where);
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
    if(_columns.at(_columns.size()-1)==",")
        _columns.remove(_columns.size()-1,1);
    return *this;
}

Builder &Builder::select(QStringList args)
{
    if(args.size())
    {
        if(_columns=="*")
            _columns.clear();

        for(int i=0; i<args.size()-1; i++)
            _columns.append(QString(" %1,").arg(args.at(i)));
        _columns.append(QString(" %1").arg(args.at(args.size()-1)));
    }
    return *this;
}



