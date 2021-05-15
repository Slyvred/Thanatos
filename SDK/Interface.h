#pragma once
#include <Windows.h>

typedef void* (__cdecl* tCreateInterface)(const char* name, int* returnCode);
void* GetInterface(const char* dllname, const char* interfacename);