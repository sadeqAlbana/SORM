#include "belongstomanyrelation.h"
#include "../model.h"
#include "../builder.h"

BelongsToManyRelation::BelongsToManyRelation(const ModelBuilder &query,
                                             const Model &parent,
                                             const QString &table,
                                             const QString &foreignPivotKey,
                                             const QString &relatedPivotKey,
                                             const QString &parentKey,
                                             const QString &relatedKey) : Relation (query,parent),
                                                                          _table(table),
                                                                          _foreignPivotKey(foreignPivotKey),
                                                                          _relatedPivotKey(relatedPivotKey),
                                                                          _parentKey(parentKey),
                                                                          _relatedKey(relatedKey)

{
    if(parentKey.isNull()){
        _parentKey=Relation::parent().primaryKey();
    }
    if(relatedKey.isNull()){
        _relatedKey=related().primaryKey();
    }
    if(foreignPivotKey.isNull()){
        _foreignPivotKey=QString("%1_%2").arg(Relation::parent().modelName().toLower()).arg(Relation::parent().primaryKey());
    }
    if(relatedPivotKey.isNull()){
        _relatedPivotKey=QString("%1_%2").arg(related().modelName().toLower()).arg(related().primaryKey());
    }


    if(Relation::parent().exists()){
        Relation::query().whereIn(QString("%1.%2").arg(related().table()).arg(_relatedKey),
                                  Builder(_table).select(_relatedPivotKey).
                                  where(_foreignPivotKey,Relation::parent().get(_parentKey)).generateSql());
    }
}

void BelongsToManyRelation::addConstraints(Collection &models)
{
    QVariantList ids;
    for(const Model &model : models){
        ids << model.get(parent().primaryKey());
    }

    Relation::query().whereIn(QString("%1.%2").arg(related().table()).arg(_relatedKey),

                              Builder(_table).select(_relatedPivotKey).
                              whereIn(_foreignPivotKey,ids).generateSql());
}

void BelongsToManyRelation::match(Collection &models)
{
    Relation::query().builder().join(_table,
                                     _relatedKey,
                                     "=",
                                     QString("%1.%2").arg(_table).arg(_relatedPivotKey));

    Collection results=get(QString("%1.* , %2").arg(related().table()).arg(_foreignPivotKey));
    for (Model &mainModel : models){
        Collection inserts;
        for (Model &relationModel : results)
        {
            if(mainModel.get(parent().primaryKey())==relationModel.get(_foreignPivotKey)){
                inserts << relationModel;
            }
        }
        mainModel.set(related().table(),inserts);
        //mainModel.setSaved();
    }
}
