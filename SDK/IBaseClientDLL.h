#pragma once
#include "VirtualMethod.h"

class ClientClass;

class IBaseClientDLL
{
public:
	VIRTUAL_METHOD(ClientClass*, GetAllClasses, 8, (), (this))
	VIRTUAL_METHOD(bool, dispatchUserMessage, 38, (int messageType, int arg, int arg1, void* data), (this, messageType, arg, arg1, data))
};