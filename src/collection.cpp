#include "collection.h"
#include <QJsonObject>
#include "model.h"
#include <QDebug>
Collection::Collection()
{

}

QVariantList Collection::primaryKeys() const
{
    QVariantList pks;
    for (int i=0; i<size(); i++)
    {
        Model model= this->at(i);
        if(model.primaryKey().isString()){
            pks << model.get(model.primaryKey().toString());
        }else{
            QStringList keys=model.primaryKey().toStringList();
            QVariantList compositePk;
            for(const QString &key : keys){
                compositePk << model.get(key);
            }
            pks << compositePk;
        }
    }
    return pks;
}

Collection::operator QJsonValue()
{
    return operator QJsonArray();
}

Collection::operator QVariant()
{
    return operator QJsonArray();
}

Collection::operator bool()
{
    return !!size();
}

Collection::operator QJsonArray()
{
    if(!size())
        return QJsonArray();
    QJsonArray array;

    for (int i=0; i<size(); i++)
    {
        array << at(i).operator QJsonObject();
    }
    return array;
}

QDebug operator <<(QDebug dbg, const Collection &collection)
{
    Model model=collection.value(0);
    QStringList columns=model.keys();
    QList<int> lengths;

    for (int i=0;i<columns.length(); i++) {
        lengths << columns[i].length();
    }

        for (int r=0; r<collection.count(); r++) {
            Model tmp=collection[r];
            for (int c=0; c<columns.size(); c++) {
             QString value=tmp[columns.at(c)].toString();
             if(value.size()>lengths.at(c))
                 lengths[c]=value.length();
            }
        }


        for (int i=0; i<columns.size(); i++) {
            QString row;
            row.append('+');
            for (int j=0;j<lengths[i]+4;j++) {
                row.append('-');
            }
            dbg.noquote().nospace()<<row;
        }
        dbg.noquote().nospace()<<"+\n";
        for (int i=0;i<columns.size();i++) {
            QString row;
            row.append('|');
            row.append(QString (" %1 ").arg(columns.at(i)));
            for (int j=row.size();j<lengths[i]+5;j++) {
                row.append(' ');
            }

           dbg.noquote().nospace()<<row;
        }
        dbg.noquote().nospace()<<"|\n";

        for (int i=0; i<columns.size(); i++) {
            QString row;
            row.append('+');
            for (int j=0;j<lengths[i]+4;j++) {
                row.append('-');
            }
            dbg.noquote().nospace()<<row;
        }
        dbg.noquote().nospace()<<"+\n";



        return dbg;
}
