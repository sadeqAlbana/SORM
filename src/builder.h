#ifndef BUILDER_H
#define BUILDER_H
#include <QString>
#include <QVariantList>
class QVariant;
class QStringList;
class QSqlRelation;
class Model;
class Collection;

struct withItem{
    QString table;
    QString primaryKey;
    QString foreignKey;
    QStringList columns;
};

class Builder
{
public:
    Builder(const QString &table,const QString pk=QString());
    Builder(const Model mdl);
    Builder &where(QString key, QVariant value);
    Builder &where(QString key,QString op, QVariant value);
    Builder &where(QString clause);
    Builder &whereIn(QString key, QVariantList values);
    Builder &whereIn(QString key, QString subQuery);
    Builder &groupBy(QString column);
    Builder &orderBy(QString column);
    Builder & join(QSqlRelation relation);
    Builder & take(int l){_limit=l; return *this;}
    Builder &skip(int offset);
    Builder &paginate(int page, int count);
    Model first();

    Collection get();
    Model find(const QVariant id);
    Collection sum(const QString field);
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


    bool insert(Model &model);
    bool update(Model &model);
    bool remove();

    Builder &with(const QString table,const QString primaryKey, const QString localKey, const QStringList columns=QStringList());




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
    QList<withItem> withList;
    QString _primaryKey;
    int _limit;
    int offset;
};

#endif // BUILDER_H
