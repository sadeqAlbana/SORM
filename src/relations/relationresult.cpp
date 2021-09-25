#include "relationresult.h"

RelationResult::RelationResult(const Model &model): _model(model), _type(Type::Model)
{

}

RelationResult::RelationResult(const Collection &collection) : _collection(collection), _type(Type::Collection)
{

}
