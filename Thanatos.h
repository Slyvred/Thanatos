#pragma once
#include <Windows.h>
#include "SDK/SDKIncludes.h"
#include "offsets.h"
#include "Entity.h"
#include "Inih/INIReader.h"
#include "Inih/ini.h"

class Thanatos
{
public:
	struct Config
	{
		std::string Nametag = "0";
		int KnifeCT = 0;
		int SkinCT = 0;
		int KnifeT = 0;
		int SkinT = 0;
	}config;

public:
	// Global vars
	intptr_t client = NULL;
	intptr_t engine = NULL;
	ClientClass* clientClass = nullptr;
	IEngineClient* EngineClient = nullptr;
	IBaseClientDLL* BaseClientDLL = nullptr;
	IModelInfoClient* ModelInfoClient = nullptr;
	IClientEntityList* ClientEntityList = nullptr;
	ICvar* Cvar = nullptr;
	Entity* localPlayer = nullptr;

public:
	// Functions that use global vars
	void Init();
	void Run();
	void Cleanup();

	void SetConvars();
	void Skinchanger(ClientFrameStage_t curStage);
	void AgentChanger(ClientFrameStage_t curStage);
	int GetModelIndex(const short itemIndex);
};