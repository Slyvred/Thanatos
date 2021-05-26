#include "Thanatos.h"
#include "Hooks/Hooks.h"
#include "Agentchanger.h"
#include "Skinchanger.h"

// For the hooks
extern Thanatos thanatos;

// CUserCmd hook
char* clientModeInterface = nullptr;
void* clientMode = nullptr;
CVMTHookManager* clientModeVMT = nullptr;
CreateMove oCreateMove = nullptr;

// FrameStageNotify hook
CVMTHookManager* baseClientDLLVMT = nullptr;
FrameStageNotify oFrameStageNotify = nullptr;
INIReader* reader = nullptr;

void __stdcall hkCreateMove(float sampleTime, CUserCmd* cmd) // Actual hooked function
{
	// Rank reveal
	if (cmd->buttons & CUserCmd::IN_SCORE)
		thanatos.BaseClientDLL->dispatchUserMessage(50, 0, 0, nullptr);

	oCreateMove(sampleTime, cmd); // restoring original function
}

void __stdcall hkFrameStageNotify(ClientFrameStage_t curStage) // Actual hooked function
{
	if (curStage == ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_START)
	{
		thanatos.Skinchanger(curStage);
		thanatos.AgentChanger(curStage);
	}

	oFrameStageNotify(curStage); // restoring original function
}

struct Convars // Storing them in a struct to avoid redefinition error
{
	ConVar* sv_cheats = nullptr;
	ConVar* cl_ragdoll_gravity = nullptr;
	ConVar* fog_override = nullptr;
	ConVar* fog_enable = nullptr;
	ConVar* mat_postprocess_enable = nullptr;
	ConVar* panorama_disable_blur = nullptr;
	ConVar* viewmodel_fov = nullptr;
}cvars;

void Thanatos::SetConvars()
{
	while (!EngineClient->isInGame()) continue;

	cvars.sv_cheats = Cvar->findVar("sv_cheats");
	cvars.sv_cheats->setValue(1);

	cvars.cl_ragdoll_gravity = Cvar->findVar("cl_ragdoll_gravity");
	cvars.cl_ragdoll_gravity->setValue(-600);

	cvars.fog_override = Cvar->findVar("fog_override");
	cvars.fog_override->setValue(1);

	cvars.fog_enable = Cvar->findVar("fog_enable");
	cvars.fog_enable->setValue(0);

	cvars.mat_postprocess_enable = Cvar->findVar("mat_postprocess_enable");
	cvars.mat_postprocess_enable->setValue(0);

	cvars.panorama_disable_blur = Cvar->findVar("@panorama_disable_blur");
	cvars.panorama_disable_blur->setValue(1);

	cvars.viewmodel_fov = Cvar->findVar("viewmodel_fov");
	cvars.viewmodel_fov->setValue(68);
}

void Thanatos::Init()
{
	// Config
	reader = new INIReader("Thanatos.ini");
	config.Nametag = reader->GetString("KNIVES", "Nametag", "0");
	config.KnifeCT = reader->GetInteger("KNIVES", "KnifeCT", 0);
	config.SkinCT = reader->GetInteger("KNIVES", "SkinCT", 0);
	config.KnifeT = reader->GetInteger("KNIVES", "KnifeT", 0);
	config.SkinT = reader->GetInteger("KNIVES", "SkinT", 0);

	// Getting their base addresses
	client = (intptr_t)GetModuleHandle("client.dll");
	engine = (intptr_t)GetModuleHandle("engine.dll");

	// Interfaces
	ClientEntityList = (IClientEntityList*)GetInterface("client.dll", "VClientEntityList003");
	EngineClient = (IEngineClient*)GetInterface("engine.dll", "VEngineClient014");
	BaseClientDLL = (IBaseClientDLL*)GetInterface("client.dll", "VClient018");
	ModelInfoClient = (IModelInfoClient*)GetInterface("engine.dll", "VModelInfoClient004");
	Cvar = (ICvar*)GetInterface("vstdlib.dll", "VEngineCvar007");
	clientClass = BaseClientDLL->GetAllClasses();

	// Grapping all of our signatures and netvars + setting convars on injection
	GetSignatures(), GetNetvars(clientClass), SetConvars();

	// Hooking CUserCmd for the rank revealer
	clientMode = **(void***)((*(uintptr_t**)(BaseClientDLL))[10] + 0x5);
	clientModeVMT = new CVMTHookManager((DWORD**)clientMode);
	oCreateMove = (CreateMove)clientModeVMT->HookMethod((DWORD)hkCreateMove, 24);

	// Hooking FSM for the skinchanger
	baseClientDLLVMT = new CVMTHookManager((DWORD**)BaseClientDLL);
	oFrameStageNotify = (FrameStageNotify)baseClientDLLVMT->HookMethod((DWORD)hkFrameStageNotify, 37);

	// Telling the user we're killing it
	EngineClient->clientCmdUnrestricted("clear");
	EngineClient->clientCmdUnrestricted("echo Thanatos Initialized !");
	EngineClient->clientCmdUnrestricted("echo Press end to eject");
	EngineClient->clientCmdUnrestricted("cl_fullupdate");
}

void Thanatos::Run() // Runs in a while loop
{
	if (!EngineClient->isInGame() && !EngineClient->IsHLTV()) // Setting the convars once when we enter a game
		SetConvars();

	if (EngineClient->isInGame())
		localPlayer = (Entity*)ClientEntityList->GetClientEntity(EngineClient->GetLocalPlayer());

	if (!localPlayer->IsValid()) return;
}

void Thanatos::Cleanup() // The name says it all
{
	// Unhooking
	baseClientDLLVMT->UnHook();
	clientModeVMT->UnHook();

	// Removing the skins
	EngineClient->clientCmdUnrestricted("cl_fullupdate");

	// Deleting global pointers
	delete clientModeVMT;
	delete baseClientDLLVMT;
	delete reader;
}