#include <Windows.h>
#include "Tanatos.h"

Tanatos tanatos;

intptr_t Main(HMODULE hMod)
{
	tanatos.Init();

	while (!GetAsyncKeyState(VK_END))
	{
		tanatos.Run();
		Sleep(1);
	}

	tanatos.Cleanup();
	FreeLibraryAndExitThread(hMod, 0);
}

BOOL APIENTRY DllMain(HMODULE hMod, intptr_t dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hMod);
		CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Main, hMod, 0, nullptr));
	}
	return TRUE;
}