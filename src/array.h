#ifndef ARRAY_H
#define ARRAY_H

class QSqlQuery;
#include <QVariant>

using QVariantMapList = QList<QVariantMap>;
class Array
{
public:
    Array(QSqlQuery query);

    operator QJsonArray() const;
    operator QJsonValue() const;

private:
    QVariantMapList m_data;

};

#endif // ARRAY_H
