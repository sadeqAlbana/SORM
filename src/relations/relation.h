#ifndef RELATION_H
#define RELATION_H
#include "../modelbuilder.h"

//https://stackoverflow.com/questions/36208460/hasmany-vs-belongstomany-in-laravel-5-x
class Relation
{
public:
    Relation(const ModelBuilder &query, const Model &parent);
    Relation(const Relation &other);
    Collection get(const QVariant &columns=QVariant());

    Model parent();
    Model related();
    virtual Relation *clone() const=0;
    virtual void      addConstraints(Collection &models)=0;
    virtual void      match(Collection &models)=0;
    //Relation &where(QString key, QVariant value);

protected:
    Model *_parent;
    ModelBuilder _query;
    ModelBuilder& query();
    //void setContraints(const QStringList &constrains);


};

#define EloquentRelation(_class) \
    virtual Relation* clone() const override{return new _class(*this);} \
    _class &where(QString key, QVariant value){query().where(key,value); return *this;}

#endif // RELATION_H
