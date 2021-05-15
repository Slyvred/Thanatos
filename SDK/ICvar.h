#pragma once
#include "VirtualMethod.h"

class ConVar;

class ICvar
{
public:
    VIRTUAL_METHOD(ConVar*, findVar, 15, (const char* name), (this, name))
};