#ifndef MODELBUILDER_H
#define MODELBUILDER_H
#include "model.h"
class ModelBuilder
{
public:
    ModelBuilder(const Model &model);
    Model model;
private:
    Model _model;
};

#endif // MODELBUILDER_H
