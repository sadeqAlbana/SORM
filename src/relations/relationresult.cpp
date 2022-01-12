/*
 * Copyright (C) 2022 Sadeq Albana
 *
 * Licensed under the GNU Lesser General Public License v3.0 :
 * https://www.gnu.org/licenses/lgpl-3.0.html
 */

#include "relationresult.h"

RelationResult::RelationResult(const Model &model): _model(model), _type(Type::Model)
{

}

RelationResult::RelationResult(const Collection &collection) : _collection(collection), _type(Type::Collection)
{

}
