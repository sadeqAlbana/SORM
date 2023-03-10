/*
 * Copyright (C) 2022 Sadeq Albana
 *
 * Licensed under the GNU Lesser General Public License v3.0 :
 * https://www.gnu.org/licenses/lgpl-3.0.html
 */

#include "belongstomanyrelation.h"
#include "../model.h"
#include "../builder.h"
#include "../collection.h"
#include "qelapsedtimer.h"
#include <QJsonArray>
BelongsToManyRelation::BelongsToManyRelation(const ModelBuilder &query,
                                             const Model &parent,
                                             const QString &table,
                                             const QString &foreignPivotKey,
                                             const QString &relatedPivotKey,
                                             const QString &parentKey,
                                             const QString &relatedKey,
                                             const QString &name) : Relation (query,parent,name),
                                                                          _table(table),
                                                                          _foreignPivotKey(foreignPivotKey),
                                                                          _relatedPivotKey(relatedPivotKey),
                                                                          _parentKey(parentKey),
                                                                          _relatedKey(relatedKey)

{
    if(parentKey.isNull()){
        _parentKey=Relation::parent().primaryKey().toString();
    }
    if(relatedKey.isNull()){
        _relatedKey=related().primaryKey().toString();
    }
    if(foreignPivotKey.isNull()){
        _foreignPivotKey=QString("%1_%2").arg(Relation::parent().modelName().toLower(),Relation::parent().primaryKey().toString());
    }
    if(relatedPivotKey.isNull()){
        _relatedPivotKey=QString("%1_%2").arg(related().modelName().toLower(),related().primaryKey().toString());
    }


    if(Relation::parent().exists()){
        Relation::query().whereIn(_relatedKey,
                                  Builder(_table).select(_relatedPivotKey).
                                  where(_foreignPivotKey,Relation::parent().get(_parentKey)).generateSql());
    }
}

BelongsToManyRelation::~BelongsToManyRelation()
{
    //qDebug()<<Q_FUNC_INFO;
}

void BelongsToManyRelation::addConstraints(Collection &models)
{
    QVariantList ids;
    for(const Model &model : models){
        ids << model.get(parent().primaryKey().toString());
    }

    Relation::query().whereIn(_relatedKey,

                              Builder(_table).select(_relatedPivotKey).
                              whereIn(_foreignPivotKey,ids).generateSql());
}

void BelongsToManyRelation::match(Collection &models)
{

    Relation::query().builder().join(_table,
                                     related().table()+"."+_relatedKey,
                                     "=",
                                     QString("%1.%2").arg(_table,_relatedPivotKey));

    Collection results=get(QString("%1.* , %2").arg(related().table(),_foreignPivotKey));
    Collection inserts;
    inserts.reserve(results.size());

//    QListIterator it(results);
    QElapsedTimer timer;

    timer.start();
    QString parentKey=parent().primaryKey().toString();
    int x=0;
//    for (Model &mainModel : models){
    for(int k=0; k<models.size(); k++){
        Model &mainModel=models[k];
        if(results.isEmpty()){
            mainModel.set(d->m_name,QVariant());
            continue;
        }

        inserts.clear();
        for(int i=0; i<results.size(); i++){
            x++;
            const auto &relationModel=results.at(i);
            if(mainModel.get(parentKey)==relationModel.get(_foreignPivotKey)){
                inserts << relationModel;
            }
        }




        mainModel.set(d->m_name,QJsonArray(inserts));
        //mainModel.setSaved();
    }

    qDebug() << "op took " << timer.elapsed() << "milliseconds";
    qDebug()<<"x: " << x;

}



