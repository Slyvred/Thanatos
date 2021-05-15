#pragma once
#include "VirtualMethod.h"
#include <iostream>

struct player_info_t
{
	char __pad0[0x8];

	int xuidlow;
	int xuidhigh;

	char name[128];
	int userid;
	char guid[33];

	char __pad1[0x17B];
};

class IEngineClient
{
public:
	VIRTUAL_METHOD(bool, getPlayerInfo, 8, (int entityIndex, player_info_t& playerInfo), (this, entityIndex, std::ref(playerInfo)))
	VIRTUAL_METHOD(int, getMaxClients, 20, (), (this))
	VIRTUAL_METHOD(bool, isInGame, 26, (), (this))
	VIRTUAL_METHOD(bool, isConnected, 27, (), (this))
	VIRTUAL_METHOD(int, GetLocalPlayer, 12, (), (this))
	VIRTUAL_METHOD(bool, IsHLTV, 93, (), (this))
	VIRTUAL_METHOD(void, clientCmdUnrestricted, 114, (const char* cmd, bool fromConsoleOrKeybind = false), (this, cmd, fromConsoleOrKeybind))
};