/*
 * Copyright (C) 2022 Sadeq Albana
 *
 * Licensed under the GNU Lesser General Public License v3.0 :
 * https://www.gnu.org/licenses/lgpl-3.0.html
 */

#include "collection.h"
#include <QJsonObject>
#include "model.h"
#include <QDebug>
Collection::Collection()
{

}

Collection::~Collection()
{
    //qDebug()<<Q_FUNC_INFO;
}

QVariantList Collection::primaryKeys() const
{
    QVariantList pks;
    for (int i=0; i<size(); i++)
    {
        Model model= this->at(i);
        if(model.primaryKey().isString()){
            pks << model.get(model.primaryKey().toString());
        }else{
            QStringList keys=model.primaryKey().toStringList();
            QVariantList compositePk;
            for(const QString &key : keys){
                compositePk << model.get(key);
            }
            pks << compositePk;
        }
    }
    return pks;
}

int Collection::page() const
{
    return m_page;
}

void Collection::setPage(int newPage)
{
    m_page = newPage;
}

int Collection::lastPage() const
{
    return m_lastPage;
}

void Collection::setLastPage(int newLastPage)
{
    m_lastPage = newLastPage;
}

Collection::operator QJsonValue()
{
    return QJsonValue(operator QJsonObject());
}

Collection::operator QJsonObject()
{
    QJsonObject object;
    object["data"]=operator QJsonArray();
    if(m_page!=-1){
        object["current_page"]=m_page;
        object["last_page"]=m_lastPage;
    }
    return object;
}

Collection::operator QVariant()
{
    return operator QJsonValue();
}

Collection::operator bool()
{
    return !!size();
}

Collection::operator QJsonArray()
{
    if(!size())
        return QJsonArray();
    QJsonArray array;

    for (int i=0; i<size(); i++)
    {
        array << at(i).operator QJsonObject();
    }
    return array;
}

QDebug operator <<(QDebug dbg, const Collection &collection)
{
    Model model=collection.value(0);
    QStringList columns=model.keys();
    QList<int> lengths;

    for (int i=0;i<columns.length(); i++) {
        lengths << columns[i].length();
    }

        for (int r=0; r<collection.count(); r++) {
            Model tmp=collection[r];
            for (int c=0; c<columns.size(); c++) {
             QString value=tmp[columns.at(c)].toString();
             if(value.size()>lengths.at(c))
                 lengths[c]=value.length();
            }
        }


        for (int i=0; i<columns.size(); i++) {
            QString row;
            row.append('+');
            for (int j=0;j<lengths[i]+4;j++) {
                row.append('-');
            }
            dbg.noquote().nospace()<<row;
        }
        dbg.noquote().nospace()<<"+\n";
        for (int i=0;i<columns.size();i++) {
            QString row;
            row.append('|');
            row.append(QString (" %1 ").arg(columns.at(i)));
            for (int j=row.size();j<lengths[i]+5;j++) {
                row.append(' ');
            }

           dbg.noquote().nospace()<<row;
        }
        dbg.noquote().nospace()<<"|\n";

        for (int i=0; i<columns.size(); i++) {
            QString row;
            row.append('+');
            for (int j=0;j<lengths[i]+4;j++) {
                row.append('-');
            }
            dbg.noquote().nospace()<<row;
        }
        dbg.noquote().nospace()<<"+\n";

        return dbg;
}
