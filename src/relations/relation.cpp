/*
 * Copyright (C) 2022 Sadeq Albana
 *
 * Licensed under the GNU Lesser General Public License v3.0 :
 * https://www.gnu.org/licenses/lgpl-3.0.html
 */

#include "relation.h"
#include "../collection.h"
#include "../model.h"
#include <QDebug>
#include "../collection.h"
#include <QJsonArray>
Relation::Relation(const ModelBuilder &query, const Model &parent, const QString &name) :
    _parent(new Model(parent)),
    _query(query),m_name(name)
{
    if(m_name.isEmpty())
        m_name=related().table();

}

Relation::Relation(const Relation &other): _parent(new Model(*other._parent)),_query(other._query), m_name(other.m_name)
{
    //qDebug()<<Q_FUNC_INFO;
}

Relation::~Relation()
{
    delete _parent;
}

Collection Relation::get(const QVariant &columns)
{
    return _query.get(columns);
}

Model Relation::parent()
{
    return *_parent;
}

Model Relation::related()
{
    return query().model();
}

//Relation &Relation::where(QString key, QVariant value)
//{
//    query().where(key,value);
//    return *this;
//}


ModelBuilder &Relation::query()
{
    return _query;
}


