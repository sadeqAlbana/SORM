/*
 * Copyright (C) 2022 Sadeq Albana
 *
 * Licensed under the GNU Lesser General Public License v3.0 :
 * https://www.gnu.org/licenses/lgpl-3.0.html
 */

#ifndef RELATION_H
#define RELATION_H
#include "../modelbuilder.h"

//https://stackoverflow.com/questions/36208460/hasmany-vs-belongstomany-in-laravel-5-x

class RelationData : public QSharedData{
public:
    RelationData(const ModelBuilder &query, const Model &parent, const QString &name=QString());
    RelationData(const RelationData &other);
    ~RelationData();
    Model *_parent; //memory leak
    ModelBuilder _query;
    QString m_name;

};

class Relation
{
public:
    Relation(const ModelBuilder &query, const Model &parent, const QString &name=QString());
    Collection get(const QVariant &columns=QVariant());

    Model parent() const;
    Model related() const;
    virtual Relation *clone() const=0;
    virtual void      addConstraints(Collection &models)=0;
    virtual void      match(Collection &models)=0;
    //Relation &where(QString key, QVariant value);
    ModelBuilder& query();
    ModelBuilder  query() const;


protected:
    QSharedDataPointer<RelationData> d;
    //void setContraints(const QStringList &constrains);
};

Q_DECLARE_TYPEINFO(Relation, Q_MOVABLE_TYPE);

#define EloquentRelation(_class) \
    virtual Relation* clone() const override{return new _class(*this);} \
    _class &where(QString key, QVariant value){query().where(key,value); return *this;} \
    _class & select(QStringList args){query().select(args); return *this;}


#endif // RELATION_H
