#pragma once
#include <Windows.h>
#include "Netvars manager/netvars_manager.h"

namespace signatures
{
	extern std::ptrdiff_t m_bDormant;
}

namespace netvars
{
	extern std::ptrdiff_t m_iTeamNum;
	extern std::ptrdiff_t m_lifeState;
	extern std::ptrdiff_t m_iAccountID;
	extern std::ptrdiff_t m_flFallbackWear;
	extern std::ptrdiff_t m_nFallbackPaintKit;
	extern std::ptrdiff_t m_iItemIDHigh;
	extern std::ptrdiff_t m_iEntityQuality;
	extern std::ptrdiff_t m_iItemDefinitionIndex;
	extern std::ptrdiff_t m_hActiveWeapon;
	extern std::ptrdiff_t m_hMyWeapons;
	extern std::ptrdiff_t m_nModelIndex;
	extern std::ptrdiff_t m_szCustomName;
	extern std::ptrdiff_t m_OriginalOwnerXuidLow;
	extern std::ptrdiff_t m_nFallbackStatTrak;
	extern std::ptrdiff_t m_nFallbackSeed;
	extern std::ptrdiff_t m_hViewModel;
	extern std::ptrdiff_t m_iViewModelIndex;
}

void GetSignatures();
void GetNetvars(ClientClass* clientClass);