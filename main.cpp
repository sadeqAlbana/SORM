#include <QCoreApplication>
#include <QSqlDatabase>
#include <QDebug>
#include "db.h"
#include "collection.h"
#include "user.h"
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


    //Model m=DB::table("users").select("id","name").where("id",2).get().first();

    //User user=User::all().first();
    User user=User::where("id",1).first();
    qDebug()<<"exists: " << user.exists();
    user.set("name","test_update2");
    user.save();


    qDebug()<<user["name"];

    return a.exec();
}
