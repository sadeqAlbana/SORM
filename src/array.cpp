#include "array.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QJsonArray>
#include <QJsonObject>
Array::Array(QSqlQuery query)
{
    QSqlRecord record=query.record();
    while(query.next()){
        QVariantMap row;
        for(int i=0; i<record.count(); i++){
            row[record.fieldName(i)]=query.value(i);
        }

        m_data << row;

    }
}

Array::operator QJsonArray() const
{
    QJsonArray array;
    for(auto &row : m_data){
        array <<QJsonObject::fromVariantMap(row);
    }

    return array;
}

Array::operator QJsonValue() const
{
    return operator QJsonArray();
}


