#include "hasmanythroughrelation.h"
#include "../modelbuilder.h"
#include "../model.h"

hasManyThroughRelation::hasManyThroughRelation(const ModelBuilder &query,
                                               const Model &farParent,
                                               const Model &throughParent,
                                               const QString &firstKey, //parent primary key
                                               const QString &secondKey, // through parent primary key
                                               const QString &localKey, //  parent foreign key
                                               const QString &secondLocalKey) : // related foreign key
    Relation (query,throughParent),
    _farParent(new Model(farParent)),
    _firstKey(firstKey),
    _secondKey(secondKey),
    _localKey(localKey),
    _secondLocalKey(secondLocalKey)
{
    if(firstKey.isNull()){
        _firstKey=parent().primaryKey();
    }
    if(secondKey.isNull()){
        _secondKey=related().primaryKey();
    }
    if(localKey.isNull()){
        _localKey=QString("%1_%2").arg(hasManyThroughRelation::farParent().modelName().toLower()).arg(hasManyThroughRelation::parent().primaryKey());
    }
    if(secondLocalKey.isNull()){
        _secondLocalKey=QString("%1_%2").arg(related().modelName().toLower()).arg(related().primaryKey());
    }


    if(Relation::parent().exists()){
        Relation::query().whereIn(QString("%1.%2").arg(related().table()).arg(_secondKey),hasManyThroughRelation::throughParent().builder().builder().select(_secondLocalKey).
                                  where(_localKey,parent().get(_firstKey)).generateSql());
    }
}

QString hasManyThroughRelation::localKey() const
{
    return _localKey;
}

Model& hasManyThroughRelation::farParent()
{
    return *_farParent;
}

void hasManyThroughRelation::addConstraints(Collection &models)
{
    QVariantList ids;
    for(const Model &model : models){
        ids << model.get(parent().primaryKey());
    }

    Relation::query().whereIn(QString("%1.%2").arg(related().table()).arg(_secondKey),

                              hasManyThroughRelation::throughParent().builder().builder().select(_secondLocalKey).
                              whereIn(_localKey,ids).generateSql());
}

void hasManyThroughRelation::match(Collection &models)
{
    Relation::query().builder().join(throughParent().table(),
                                     related().primaryKey(),
                                     "=",
                                     QString("%1.%2").arg(throughParent().table()).arg(secondLocalKey()));

    Collection results=get(QString("%1.* , %2").arg(related().table()).arg(localKey()));
    for (Model &mainModel : models){
        Collection inserts;
        for (Model &relationModel : results)
        {
            if(mainModel.get(parent().primaryKey())==relationModel.get(localKey())){
                inserts << relationModel;
            }
        }
        mainModel.set(related().table(),inserts);
        //mainModel.setSaved();
    }
}

QString hasManyThroughRelation::firstKey() const
{
    return _firstKey;
}

QString hasManyThroughRelation::secondKey() const
{
    return _secondKey;
}

QString hasManyThroughRelation::secondLocalKey() const
{
    return _secondLocalKey;
}

Model hasManyThroughRelation::throughParent()
{
    return parent();
}
