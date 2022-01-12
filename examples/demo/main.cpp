#include <QCoreApplication>
#include <QSqlDatabase>
#include <QDebug>
#include "user.h"
#include "post.h"
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
    qDebug()<<user["name"];

    Collection transactions=user.hasMany<Post>().get();


    qDebug()<<transactions[1]["total"];

    QString r=R"(
  -------------------------
  | id | name | password |
  |    |      |          |


              )";

qDebug()<<transactions;


    return a.exec();
}
