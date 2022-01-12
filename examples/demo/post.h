#ifndef POST_H
#define POST_H

#include <model.h>

class Post : public Model
{
    ELOQUENT_MODEL(Post, Posts, "id",true,true)
public:
    void setID(const int &id){set("id",id);}
    int id() const{return get("id").toInt();}
    QString title() const{return get("title").toString();}
    void setTitle(const QString &title){set("title",title);}
};

#endif // POST_H
