#ifndef BUILDER_H
#define BUILDER_H
#include <QSqlQuery>
class Collection;
class Builder
{
public:
    Builder(const QString &table);
    Collection get();
    Builder &select();
    Builder & select(QStringList columns);

    template<typename First, typename ... Strings>
    Builder & select(First arg, const Strings&... rest)
    {
        if(_columns=="*")
            _columns.clear();

        _columns.append(QString(" %1,").arg(arg));

        return select(rest...);
    }


    QSqlQuery _query;

private:
    QString _table;
    QString _columns;

};

#endif // BUILDER_H
