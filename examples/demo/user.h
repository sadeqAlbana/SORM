#ifndef USER_H
#define USER_H
#include <model.h>
class User : public Model
{
    ELOQUENT_MODEL(User, users, "id",true,true)
public:
    void setID(const int &id){set("id",id);}
    void setUsername(const QString &username){set("username",username);}
    void setPassword(const QString &password){set("password",password);}
    int id() const{return get("id").toInt();}
    QString username() const{ return get("username").toString();}
    QString password() const {return get("password").toString();}

};

#endif // USER_H
