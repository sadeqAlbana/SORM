/*
 * Copyright (C) 2022 Sadeq Albana
 *
 * Licensed under the GNU Lesser General Public License v3.0 :
 * https://www.gnu.org/licenses/lgpl-3.0.html
 */

#ifndef BUILDER_H
#define BUILDER_H
#include <QString>
#include <QVariantList>
#include <QMap>
#include <QSqlQuery>
class QVariant;
#include <QStringList>
class QSqlRelation;
class Collection;

class QSqlRecord;


class Builder
{
public:
    Builder(const QString &table);
    ~Builder();
    Builder &where(QString key, QVariant value); //not perfect
    Builder &where(QString key,QString op, QVariant value); //not perfect
    Builder &whereRaw(QString clause);
    Builder &orWhere(QString key, QVariant value); //not perfect
    Builder &orWhere(QString key,QString op, QVariant value); //not perfect
    Builder &orWhereRaw(QString clause);

    Builder &whereIn(QString key, QVariantList values); //not perfect
    Builder &orWhereIn(QString key, QVariantList values); //not perfect

    Builder &whereIn(QString key, QString subQuery);
    Builder &orWhereIn(QString key, QString subQuery);

    Builder &groupBy(QString column);
    Builder &orderBy(QString column,const QString &direction=QStringLiteral("asc"));
    Builder & take(int l){_limit=l; return *this;}
    Builder &skip(int offset);
    Builder &simplePaginate(int page, int count);
    Builder &join(const QString &table,const QString &first,const QString op, const QString &second);

    QSqlQuery get();
    QVariant sum(const QString &field);
    QVariant max(const QString &field);
    int  count(const QString &field="*");

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


    bool insert(const QVariantMap &map);
    bool update(const QVariantMap &map);
    bool remove();

    QVariant lastInsertId() const;

    bool executeQuery(QSqlQuery &query, const QString &statement=QString());


private:
    QString escapeKey(const QString &key) const;
    QString escapeTable(const QString &table=QString()) const;
    QString tableClause;
    QString columnsClause;
    QString orderByClause;
    QString whereClause;
    QString groupByClause;
    QString joinClause;
    QString sumClause;
    QString dbDriver;
    int _limit;
    int offset=0;
    QVariant m_lastInsertId;
    //QSqlQuery _sqlQuery;

    friend class ModelBuilder;
};


#endif // BUILDER_H
