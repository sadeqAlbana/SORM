#ifndef RELATION_H
#define RELATION_H
#include "../modelbuilder.h"
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


protected:
    Model *_parent;
    ModelBuilder _query;
    ModelBuilder& query();
    void setContraints(const QStringList &constrains);


};

#define EloquentRelation(_class) \
    virtual Relation* clone() const override{return new _class(*this);}

#endif // RELATION_H
