/*
 * Copyright (C) 2022 Sadeq Albana
 *
 * Licensed under the GNU Lesser General Public License v3.0 :
 * https://www.gnu.org/licenses/lgpl-3.0.html
 */

#include "relationresult.h"

RelationResult::RelationResult(const Model &model): m_data(model), m_type(Type::Model)
{

}

RelationResult::RelationResult(const Collection &collection) : m_data(collection), m_type(Type::Collection)
{

}


RelationResultData::~RelationResultData()
{
    //qDebug()<<Q_FUNC_INFO;
}
