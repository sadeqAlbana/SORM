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

union RelationResultData{
public:
    RelationResultData(const Collection &collection): m_collection(collection){}
    RelationResultData(const Model &model) : m_model(model){}
    ~RelationResultData(){}
    Collection m_collection;
    Model m_model;
};

class RelationResult
{
public:
    enum class Type{
      Model = 0,
      Collection = 1
    };

    RelationResult(const Model &model);
    RelationResult(const Collection &collection);
    RelationResultData m_data;
    inline const Type& type(){return m_type;}
    Type m_type;
};

#endif // RELATIONRESULT_H
