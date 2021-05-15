#pragma once
#include "VirtualMethod.h"

class model_t;

class IModelInfoClient
{
public:
	VIRTUAL_METHOD(const model_t*, GetModel, 1, (int modelIndex), (this, modelIndex))
	VIRTUAL_METHOD(int, GetModelIndex, 2, (const char* name), (this, name))
	VIRTUAL_METHOD(const char*, GetModelName, 3, (const model_t* model), (this, model))
};