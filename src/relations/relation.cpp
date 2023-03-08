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
    d(new RelationData(query,parent,name))
{


}





Relation::~Relation()
{
//    delete _parent;
}

Collection Relation::get(const QVariant &columns)
{
    return d->_query.get(columns);
}

Model Relation::parent() const
{
    return *d->_parent;
}

Model Relation::related() const
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
    return d->_query;
}

ModelBuilder Relation::query() const
{
    return d->_query;
}



RelationData::RelationData(const ModelBuilder &query, const Model &parent, const QString &name): QSharedData(),    _parent(new Model(parent)),
   _query(query),m_name(name)

{
    if(m_name.isEmpty())
        m_name=_query.model().table();
}

RelationData::~RelationData()
{
    if(_parent)
        delete _parent;
}
