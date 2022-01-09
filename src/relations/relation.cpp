#include "relation.h"
#include "../collection.h"
#include "../model.h"
#include <QDebug>
Relation::Relation(const ModelBuilder &query, const Model &parent, const QString &name) :
    _parent(new Model(parent)),
    _query(query),m_name(name)
{
    if(m_name.isEmpty())
        m_name=related().table();

}

Relation::Relation(const Relation &other): _parent(new Model(*other._parent)),_query(other._query), m_name(other.m_name)
{

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


