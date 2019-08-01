#include "collection.h"
#include <QJsonObject>
#include "model.h"
#include <QDebug>
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

QDebug operator <<(QDebug dbg, const Collection &collection)
{
    Model model=collection.value(0);
    QStringList columns=model.keys();
    QList<int> lengths;

    for (int i=0;i<columns.length(); i++) {
        lengths << 0;
    }

        for (int r=0; r<collection.count(); r++) {
            Model tmp=collection[r];
            for (int c=0; columns.size(); c++) {
             QString value=tmp[columns.at(c)].toString();
             if(value.size()>lengths.at(c))
                 lengths[c]=value.length();
            }
        }

        for (int i=0; columns.size(); i++) {
            QString row;

        }


}
