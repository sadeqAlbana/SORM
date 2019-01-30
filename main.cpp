#include <QCoreApplication>
#include <QSqlDatabase>
#include <QDebug>
#include "db.h"
#include "collection.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("pos");
    db.setHostName("localhost");
    db.setPort(3306);
    db.setUserName("root");
    db.setPassword("root");
    db.open();


    Model m=DB::table("users").select("id","name").where("id",2).get().first();


    qDebug()<<m.get("name");

    return a.exec();
}
