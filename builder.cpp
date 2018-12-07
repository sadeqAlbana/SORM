#include "builder.h"
#include "collection.h"
Builder::Builder(const QString &table) :
_table(table),
  _columns("*")
{

}

Collection Builder::get()
{
    QString qry=QString("select %1 from %2").arg(_columns).arg(_table);
}

Builder &Builder::select()
{
    if(_columns.at(_columns.size()-1)==",")
        _columns.remove(_columns.size()-1,1);
    return *this;
}

Builder &Builder::select(QStringList columns)
{

    return *this;
}



