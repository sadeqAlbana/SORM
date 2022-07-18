/*
 * Copyright (C) 2022 Sadeq Albana
 *
 * Licensed under the GNU Lesser General Public License v3.0 :
 * https://www.gnu.org/licenses/lgpl-3.0.html
 */

#include "modelbuilder.h"
#include "model.h"
#include "collection.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDateTime>
#include "relations/relation.h"
#include <QDebug>
#include <QSharedPointer>
#include <QSqlError>
#include "relations/relationlist.h"
ModelBuilder::ModelBuilder(const Model &model) :_model(new Model(model)),_builder(_model->table())
{

}

ModelBuilder::ModelBuilder(const ModelBuilder &other) : _model(new Model(*other._model)),_builder(other._builder),relations(other.relations)
{

}

ModelBuilder::~ModelBuilder()
{
   //qDebug()<<Q_FUNC_INFO;
   delete _model;
}

ModelBuilder::ModelBuilder(const QString &table, const PrimaryKey &primaryKey, const QString &modelName, const bool &usesTimestamps, const bool &usesAutoIncrement) :
    _model(new Model(table,primaryKey,modelName,usesTimestamps,usesAutoIncrement)),_builder(table)
{

}

Model ModelBuilder::model() const
{
    return *_model;
}



Collection ModelBuilder::get(const QVariant &column)
{
    if(column.isValid())
    {
        switch (column.type()) {
        case QMetaType::QStringList : builder().select(column.toStringList()); break;
        case QMetaType::QString     : builder().select(column.toString())    ; break;
        default:                                                               break;
        }
    }

    if(model().usesTimestamps()){
        builder().whereRaw(QString("%1 is null").arg(builder().escapeKey("deleted_at")));
    }

    QSqlQuery query=builder().get();

    int lastPage=-1;
    if(m_page!=-1){
        int totalCount=query.size();
        float pageCount=(double)totalCount/(double)m_count;
        if(pageCount<1)
            pageCount=1;

        qDebug()<<"count before: " << pageCount;



        if(m_page>pageCount){
            m_page=pageCount;
        }
        if(m_page<pageCount){
            this->simplePaginate(m_page,m_count);
        }
        else{
           this->simplePaginate(m_page,m_count);
        }
        query=builder().get();
        lastPage=pageCount;
    }

    if(query.lastError().type()==QSqlError::NoError) //was if(query.exec()).........possible bug ?
    {
        Collection collection;
        collection.setLastPage(lastPage);
        collection.setPage(m_page);
        QSqlRecord record=query.record();
        while (query.next()) {
            Model m(model());
            for(int i=0; i<record.count(); i++)
            {
                m.set(record.fieldName(i),query.value(i));
                m.setSaved();
            }
            collection << m;

        }

        if(!collection.isEmpty()){
            for(Relation *relation : relations)
            {
                relation->addConstraints(collection);
                relation->match(collection);
            }
        }



        return collection;
    }
    return Collection();
}

ModelBuilder &ModelBuilder::where(QString key, QVariant value)
{
    builder().where(key,value);
    return *this;
}

ModelBuilder &ModelBuilder::where(QString key, QString op, QVariant value)
{
    builder().where(key,op,value);
    return *this;
}

ModelBuilder &ModelBuilder::orWhere(QString key, QVariant value)
{
    builder().orWhere(key,value);
    return *this;
}

ModelBuilder &ModelBuilder::orWhere(QString key, QString op, QVariant value)
{
    builder().orWhere(key,op,value);
    return *this;
}

ModelBuilder &ModelBuilder::whereRaw(QString clause)
{
    builder().whereRaw(clause);
    return *this;
}

ModelBuilder &ModelBuilder::orWhereRaw(QString clause)
{
    builder().orWhereRaw(clause);
    return *this;
}

ModelBuilder &ModelBuilder::whereIn(QString key, QVariantList values)
{
    builder().whereIn(key,values);

    return *this;
}

ModelBuilder &ModelBuilder::whereIn(QString key, QString subQuery)
{
    builder().whereIn(key,subQuery);

    return *this;
}

ModelBuilder &ModelBuilder::whereNotIn(QString key, QVariantList values)
{
    builder().whereNotIn(key,values);

    return *this;
}

ModelBuilder &ModelBuilder::whereNotIn(QString key, QString subQuery)
{
    builder().whereNotIn(key,subQuery);

    return *this;
}

ModelBuilder &ModelBuilder::with(const Relation &relation)
{
    relations << relation.clone();
    return *this;
}

ModelBuilder &ModelBuilder::with(const RelationList &relations)
{
    for(const Relation * const &relation : relations){
        this->relations << relation->clone();
    }
    return *this;
}

ModelBuilder &ModelBuilder::groupBy(QString column)
{
    builder().groupBy(column);
    return *this;
}

ModelBuilder &ModelBuilder::orderBy(QString column, const QString &direction)
{
    builder().orderBy(column,direction);
    return *this;
}



Model ModelBuilder::first()
{
    builder().take(1);
    return get().value(0);
}

bool ModelBuilder::insert(Model &mdl)
{
    if(mdl.usesTimestamps())
    {
        QDateTime now=QDateTime::currentDateTime();
        mdl.set("created_at",now);
        //mdl.set("updated_at",now);
    }

    bool success= builder().insert(mdl.data);
    if(success){
        QVariant lastInsertId=builder().lastInsertId();
        if(lastInsertId.isValid() && mdl._incrementing){
            mdl.set(mdl.primaryKey().toString(),lastInsertId);
        }
        mdl.setSaved();
    }
    return success;
}

bool ModelBuilder::update(Model &mdl)
{

    if(mdl.usesTimestamps())
    {
        QDateTime now=QDateTime::currentDateTime();
        mdl.set("updated_at",now);
    }

    /*the behaviour is everytime you call seve, the timestamp gets updated even if not data are modified,
    simetimes, if you call Model::save() more than monce, QDateTime::currentDateTime will return the same timestamp and will result in an SQL syntax error
    the code below fixes this issue*/
    if(mdl.dirtyKeys().isEmpty()){
        return true; //just ignore it and pretend that it is saved
    }


    QVariantMap updateData;
    for (auto key : mdl.dirtyKeys()) {
     updateData[key]=mdl[key];
    }

    if(mdl.primaryKey().isList())
    {
        QStringList primaryKeys=mdl.primaryKey().toStringList();
        for(const QString &key : primaryKeys){
            builder().where(key,mdl.get(key));
        }
    }
    else{
       builder().where(model().primaryKey().toString(),mdl.get(model().primaryKey().toString()));
    }


    bool result=builder().update(updateData);
    mdl.setSaved();

    return result;
}

bool ModelBuilder::remove(Model &model)
{
    if(!model.exists())
        return false;

    if(model.primaryKey().isList()){
        QStringList primaryKeys=model.primaryKey().toStringList();
        for(const QString &key : primaryKeys){
            builder().where(key,model.get(key));
        }
    }
    else
        builder().where(model.primaryKey().toString(),model.get(model.primaryKey().toString()));


    bool success=false;
    if(model.usesTimestamps()){
        model.set("deleted_at",QDateTime::currentDateTime());
        success=update(model);
    }else{
        success=builder().remove();
    }

    if(success){
        model._exists=false;
    }

    return success;
}

ModelBuilder &ModelBuilder::simplePaginate(int page, int count)
{
    builder().simplePaginate(page,count);

    return *this;
}

ModelBuilder &ModelBuilder::paginate(int page, int count)
{
    m_page=page;
    m_count=count;
    return *this;
}



