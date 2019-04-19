#ifndef BUILDER_H
#define BUILDER_H
#include <QString>
class QVariant;
class QStringList;
class QSqlRelation;
class Model;
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
    Builder & take(int l){_limit=l; return *this;}
    Builder &skip(int offset);
    Builder &paginate(int page, int count);
    Model first();

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
    bool remove();




private:
    QString escapeKey(const QString &key) const;
    QString escapeTable() const;
    QString tableClause;
    QString columnsClause;
    QString orderByClause;
    QString whereClause;
    QString groupByClause;
    int _limit;
    int offset;

};

#endif // BUILDER_H
