#include <Windows.h>
#include "Thanatos.h"

Thanatos thanatos;

intptr_t Main(HMODULE hMod)
{
	thanatos.Init();

	while (!GetAsyncKeyState(VK_END))
	{
		thanatos.Run();
		Sleep(5);
	}

	thanatos.Cleanup();
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