#include <QCoreApplication>
#include <QSqlDatabase>
#include <QDebug>
#include "user.h"
#include "post.h"
#include <QSettings>
#include <QSqlResult>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QSettings settings(QCoreApplication::applicationDirPath()+"/.env.ini",QSettings::IniFormat,&a);
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName(settings.value("db_name").toString());
    db.setHostName(settings.value("db_host").toString());
    db.setPort(settings.value("db_port").toInt());
    db.setUserName(settings.value("db_username").toString());
    db.setPassword(settings.value("db_password").toString());
    db.open();

    qDebug()<<sizeof(QSqlResult);


    Model m;
    m["a"]="x";
    //m.set("a",1);
    m.save();

    Model m2=m;
    //m2.set("a",3);


    //m2.save();

    qDebug()<<m2.get("a");
    qDebug()<<m.get("a");
    //Model m=DB::table("users").select("id","name").where("id",2).get().first();

    //User user=User::all().first();
//    User user=User::where("id",1).first();
//    qDebug()<<"exists: " << user.exists();
//    user.set("name","test_update2");
//    qDebug()<<user["name"];

//    Collection transactions=user.hasMany<Post>().get();





    return a.exec();
}
