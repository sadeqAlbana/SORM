#include "hasmanyrelation.h"
#include "../builder.h"
HasManyRelation::HasManyRelation(Model parent, Builder query, QString foreignKey, QString localKey) : Relation (parent,query)
{

    if(foreignKey.isNull())
        foreignKey=QString("%1_%2").arg(parent.modelName()).arg(parent.getPrimaryKey());

    if(localKey.isNull())
        localKey=parent.getPrimaryKey();

    _builder.where(foreignKey,parent.get(localKey));
}
