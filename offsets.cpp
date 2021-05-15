#include "offsets.h"
#include "Netvars manager/netvars_manager.h"
#include "Pattern scanner/PatternScanner.h"

namespace signatures
{
	std::ptrdiff_t m_bDormant;
}

namespace netvars
{
	std::ptrdiff_t m_iTeamNum;
	std::ptrdiff_t m_lifeState;
	std::ptrdiff_t m_iAccountID;
	std::ptrdiff_t m_flFallbackWear;
	std::ptrdiff_t m_nFallbackPaintKit;
	std::ptrdiff_t m_iItemIDHigh;
	std::ptrdiff_t m_iEntityQuality;
	std::ptrdiff_t m_iItemDefinitionIndex;
	std::ptrdiff_t m_hActiveWeapon;
	std::ptrdiff_t m_hMyWeapons;
	std::ptrdiff_t m_nModelIndex;
	std::ptrdiff_t m_szCustomName;
	std::ptrdiff_t m_OriginalOwnerXuidLow;
	std::ptrdiff_t m_nFallbackStatTrak;
	std::ptrdiff_t m_nFallbackSeed;
	std::ptrdiff_t m_hViewModel;
	std::ptrdiff_t m_iViewModelIndex;
}

// Sig found on Haze Dumper
void GetSignatures()
{
	signatures::m_bDormant = Scan("client.dll", "\x8A\x81\x00\x00\x00\x00\xC3\x32\xC0", "xx????xxx", 0x2, 0x8) & 0xFF;
}


// offsets and table names found on Haze Dumper
void GetNetvars(ClientClass* clientClass)
{
	netvars::m_iTeamNum = GetNetvarOffset("DT_BasePlayer", "m_iTeamNum", clientClass);
	netvars::m_hViewModel = GetNetvarOffset("DT_BasePlayer", "m_hViewModel[0]", clientClass);
	netvars::m_iAccountID = GetNetvarOffset("DT_BaseAttributableItem", "m_iAccountID", clientClass);
	netvars::m_flFallbackWear = GetNetvarOffset("DT_BaseAttributableItem", "m_flFallbackWear", clientClass);
	netvars::m_nFallbackPaintKit = GetNetvarOffset("DT_BaseAttributableItem", "m_nFallbackPaintKit", clientClass);
	netvars::m_iItemIDHigh = GetNetvarOffset("DT_BaseAttributableItem", "m_iItemIDHigh", clientClass);
	netvars::m_iEntityQuality = GetNetvarOffset("DT_BaseAttributableItem", "m_iEntityQuality", clientClass);
	netvars::m_iItemDefinitionIndex = GetNetvarOffset("DT_BaseAttributableItem", "m_iItemDefinitionIndex", clientClass);
	netvars::m_szCustomName = GetNetvarOffset("DT_BaseAttributableItem", "m_szCustomName", clientClass);
	netvars::m_OriginalOwnerXuidLow = GetNetvarOffset("DT_BaseAttributableItem", "m_OriginalOwnerXuidLow", clientClass);
	netvars::m_nFallbackStatTrak = GetNetvarOffset("DT_BaseAttributableItem", "m_nFallbackStatTrak", clientClass);
	netvars::m_nFallbackSeed = GetNetvarOffset("DT_BaseAttributableItem", "m_nFallbackSeed", clientClass);
	netvars::m_iAccountID = GetNetvarOffset("DT_BaseAttributableItem", "m_iAccountID", clientClass);
	netvars::m_hActiveWeapon = GetNetvarOffset("DT_BaseCombatCharacter", "m_hActiveWeapon", clientClass);
	netvars::m_hMyWeapons = GetNetvarOffset("DT_BaseCombatCharacter", "m_hMyWeapons", clientClass);
	netvars::m_nModelIndex = GetNetvarOffset("DT_BaseViewModel", "m_nModelIndex", clientClass);
	netvars::m_iViewModelIndex = GetNetvarOffset("DT_BaseCombatWeapon", "m_iViewModelIndex", clientClass);
}