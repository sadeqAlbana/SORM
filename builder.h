#ifndef BUILDER_H
#define BUILDER_H
#include <QSqlQuery>
#include <QSqlRelation>
#include "model.h"
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
        if(columnsClause=="*")
            columnsClause.clear();

        columnsClause.append(QString(" %1,").arg(arg));

        return select(rest...);
    }


    bool insert(Model &model);
    bool update(Model &model);




private:
    QString tableClause;
    QString columnsClause;
    QString orderByClause;
    QString whereClause;
    QString groupByClause;
    int _limit;

};

#endif // BUILDER_H
