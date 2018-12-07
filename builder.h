#ifndef BUILDER_H
#define BUILDER_H
#include <QSqlQuery>
#include <QSqlRelation>
class Collection;
class Builder
{
public:
    Builder(const QString &table);
    Builder &where(QString key, QVariant value);
    Builder &where(QString clause);
    Builder &groupBy(QString key);
    Builder &orderBy(QString key);
    Builder & join(QSqlRelation relation);
    Builder & limit(int l){_limit=l; return *this;}

    Collection get();
    Builder &select();
    Builder & select(QStringList args);

    template<typename First, typename ... Strings>
    Builder & select(First arg, const Strings&... rest)
    {
        if(_columns=="*")
            _columns.clear();

        _columns.append(QString(" %1,").arg(arg));

        return select(rest...);
    }

private:
    QString _table;
    QString _columns;
    QString _orderBy;
    QString _where;
    QString _groupBy;
    int _limit;

};

#endif // BUILDER_H
