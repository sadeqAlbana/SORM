/*
 * Copyright (C) 2022 Sadeq Albana
 *
 * Licensed under the GNU Lesser General Public License v3.0 :
 * https://www.gnu.org/licenses/lgpl-3.0.html
 */

#ifndef RELATIONRESULT_H
#define RELATIONRESULT_H
#include "../model.h"
#include "../collection.h"


class RelationResult
{
public:
    enum class Type{
      Model = 0,
      Collection = 1
    };

    RelationResult(const Model &model);
    RelationResult(const Collection &collection);
    Model _model;
    Collection _collection;
    inline const Type& type(){return _type;}
    Type _type;
};

#endif // RELATIONRESULT_H
