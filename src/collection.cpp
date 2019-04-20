#include "collection.h"
#include <QJsonObject>
#include "model.h"
Collection::Collection()
{

}

Collection::operator bool()
{
    return !!size();
}

Collection::operator QJsonArray()
{
    QStringList keys=first().keys();

    QJsonArray array;

    for (int i=0; i<size(); i++)
    {
        const Model &model=at(i);
        QJsonObject obj;
        for(QString key : keys)
            obj.insert(key,model.get(key).toString());

        array << obj;
    }

    return array;
}
