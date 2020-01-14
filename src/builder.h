#ifndef BUILDER_H
#define BUILDER_H
#include <QString>
#include <QVariantList>
#include <QMap>
class QVariant;
class QStringList;
class QSqlRelation;
class Collection;
class QSqlQuery;
class QSqlRecord;

using Map = QMap<QString,QVariant>;

class Builder
{
public:
    Builder(const QString &table);
    Builder &where(QString key, QVariant value);
    Builder &where(QString key,QString op, QVariant value);
    Builder &where(QString clause);
    Builder &whereIn(QString key, QVariantList values);
    Builder &whereIn(QString key, QString subQuery);
    Builder &groupBy(QString column);
    Builder &orderBy(QString column);
    Builder & take(int l){_limit=l; return *this;}
    Builder &skip(int offset);
    Builder &paginate(int page, int count);

    QSqlQuery get();
    QSqlQuery sum(const QString field);
    QString generateSql();
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


    bool insert(const Map &map);
    bool update(const Map &map);
    bool remove();




private:
    QString escapeKey(const QString &key) const;
    QString escapeTable() const;
    QString tableClause;
    QString columnsClause;
    QString orderByClause;
    QString whereClause;
    QString groupByClause;
    QString sumClause;
    QString dbDriver;
    int _limit;
    int offset;

};

#endif // BUILDER_H
