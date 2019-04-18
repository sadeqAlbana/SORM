#ifndef ELOQUENTMODEL_H
#define ELOQUENTMODEL_H
#include "QString"
#include "builder.h"
#include "collection.h"
#define ELOQUENT_MODEL(_class, tableName,_primaryKey) \
    public: \
        _class() {} \
        _class(Model model) : Model(model){} \
        static QString table(){return #tableName;} \
        static QString primaryKey(){return #_primaryKey;} \
        static Collection all(){return Builder(table()).get();} \
    private:
#endif // ELOQUENTMODEL_H
