#ifndef DB_H
#define DB_H
class Builder;
class QString;
class DB
{
public:
    DB();

    static Builder table(const QString &table);

};

#endif // DB_H
