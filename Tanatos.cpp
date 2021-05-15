#include "Tanatos.h"
#include "Hooks/Hooks.h"
#include "Skinchanger.h"

// For the hooks
extern Tanatos tanatos;

// CUserCmd hook
char* clientModeInterface = nullptr;
void* clientMode = nullptr;
CVMTHookManager* clientModeVMT = nullptr;
CreateMove oCreateMove = nullptr;

// FrameStageNotify hook
CVMTHookManager* baseClientDLLVMT = nullptr;
FrameStageNotify oFrameStageNotify = nullptr;
INIReader* reader = nullptr;

void __stdcall hkCreateMove(float sampleTime, CUserCmd* cmd)
{
	// Rank reveal
	if (cmd->buttons & CUserCmd::IN_SCORE)
		tanatos.BaseClientDLL->dispatchUserMessage(50, 0, 0, nullptr);

	oCreateMove(sampleTime, cmd); // restoring original function
}

void __stdcall hkFrameStageNotify(ClientFrameStage_t curStage)
{
	tanatos.Skinchanger(curStage);
	oFrameStageNotify(curStage); // restoring original function
}

void Tanatos::Init()
{
	// Config
	reader = new INIReader("Tanatos.ini");
	config.Nametag = reader->GetString("KNIVES", "Nametag", "0");
	config.KnifeCT = reader->GetInteger("KNIVES", "KnifeCT", 0);
	config.SkinCT = reader->GetInteger("KNIVES", "SkinCT", 0);
	config.KnifeT = reader->GetInteger("KNIVES", "KnifeT", 0);
	config.SkinT = reader->GetInteger("KNIVES", "SkinT", 0);

	// Dlls
	client = (intptr_t)GetModuleHandle("client.dll");
	engine = (intptr_t)GetModuleHandle("engine.dll");

	// Interfaces
	ClientEntityList = (IClientEntityList*)GetInterface("client.dll", "VClientEntityList003");
	EngineClient = (IEngineClient*)GetInterface("engine.dll", "VEngineClient014");
	BaseClientDLL = (IBaseClientDLL*)GetInterface("client.dll", "VClient018");
	ModelInfoClient = (IModelInfoClient*)GetInterface("engine.dll", "VModelInfoClient004");
	//Cvar = (ICvar*)GetInterface("vstdlib.dll", "VEngineCvar007");
	clientClass = BaseClientDLL->GetAllClasses();

	GetSignatures(), GetNetvars(clientClass);

	// Hooking CUserCmd for the rank revealer
	clientMode = **(void***)((*(uintptr_t**)(BaseClientDLL))[10] + 0x5);
	clientModeVMT = new CVMTHookManager((DWORD**)clientMode);
	oCreateMove = (CreateMove)clientModeVMT->HookMethod((DWORD)hkCreateMove, 24);

	// Hooking FSM for the skinchanger
	baseClientDLLVMT = new CVMTHookManager((DWORD**)BaseClientDLL);
	oFrameStageNotify = (FrameStageNotify)baseClientDLLVMT->HookMethod((DWORD)hkFrameStageNotify, 37);

	// Telling we're killing it
	EngineClient->clientCmdUnrestricted("clear");
	EngineClient->clientCmdUnrestricted("echo Tanatos Initialized !");
}

void Tanatos::Run() // Runs in a while loop
{
	if (EngineClient->isInGame())
		localPlayer = (Entity*)ClientEntityList->GetClientEntity(EngineClient->GetLocalPlayer());

	if (!localPlayer->IsValid()) return;
}

//void Tanatos::SetConvars()
//{
//	while (!EngineClient->isInGame()) continue;
//
//	ConVar* sv_cheats = Cvar->findVar("sv_cheats");
//	sv_cheats->setValue(1);
//
//	ConVar* cl_ragdoll_gravity = Cvar->findVar("cl_ragdoll_gravity");
//	cl_ragdoll_gravity->setValue(-600);
//
//	ConVar* fog_override = Cvar->findVar("fog_override");
//	fog_override->setValue(1);
//
//	ConVar* fog_enable = Cvar->findVar("fog_enable");
//	fog_enable->setValue(0);
//
//	ConVar* mat_postprocess_enable = Cvar->findVar("mat_postprocess_enable");
//	mat_postprocess_enable->setValue(0);
//
//	ConVar* panorama_disable_blur = Cvar->findVar("@panorama_disable_blur");
//	panorama_disable_blur->setValue(1);
//
//	ConVar* viewmodel_fov = Cvar->findVar("viewmodel_fov");
//	viewmodel_fov->setValue(68);
//}

void Tanatos::Cleanup() // The name says it all
{
	baseClientDLLVMT->UnHook();
	clientModeVMT->UnHook();

	delete clientModeVMT;
	delete baseClientDLLVMT;
	delete reader;
}