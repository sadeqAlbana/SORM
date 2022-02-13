# SORM

Eloquent like ORM for Qt


## Usage

```c++
//basic usage
    User user=User::find(1);
    qDebug()<<"exists: " << user.exists();
    user.set("name","test_update2");
    user.save();
    qDebug()<<user["name"];

//relations
    Collection transactions=user.hasMany<Post>().get();
    qDebug()<<transactions[0]["total"];

```

## A word of gratitude
This project is inspired by [Infinity](https://github.com/foreshadow)'s [
Inloquent ](https://github.com/foreshadow/Inloquent).
It's similiar in syntax but different in it's internal structure, and has many more features like relations support.

## Disclaimer
This is a hobby/study project, It's API/public interface is subject to change without a prior notice !

## License
GNU Lesser General Public License v3.0. See LICENSE file
