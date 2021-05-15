#include "PatternScanner.h"
// https://youtu.be/mKUSLJjlajg

MODULEINFO GetModuleInfo(const char* szModule)
{
    MODULEINFO modInfo = { 0 };
    HMODULE hModule = GetModuleHandle(szModule);
    if (hModule == 0) return modInfo;

    GetModuleInformation(GetCurrentProcess(), hModule, &modInfo, sizeof(MODULEINFO));
    return modInfo;
}

intptr_t FindPattern(const char* mod, const char* pattern, const char* mask)
{
    MODULEINFO mInfo = GetModuleInfo(mod);

    intptr_t base = (intptr_t)mInfo.lpBaseOfDll;
    intptr_t size = (intptr_t)mInfo.SizeOfImage;

    intptr_t patternLength = (intptr_t)strlen(mask);

    for (intptr_t i = 0; i < size - patternLength; i++)
    {
        bool found = true;

        for (intptr_t j = 0; j < patternLength; j++)
        {
            found &= mask[j] == '?' || pattern[j] == *(char*)(base + i + j);
        }

        if (found) return base + i;
    }
    return 0; // = Fail
}

intptr_t Scan(const char* mod, const char* pattern, const char* mask, int offset, int extra) // My own code
{
    intptr_t Sig = FindPattern(mod, pattern, mask);
    Sig = (*(intptr_t*)(Sig + offset) - (intptr_t)GetModuleHandle(mod)) + extra;
    return Sig;
}