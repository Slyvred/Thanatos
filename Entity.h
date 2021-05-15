#pragma once
enum class LifeState
{
	LIFE_ALIVE,
	LIFE_DYING,
	LIFE_DEAD,
	LIFE_RESPAWNABLE,
	LIFE_DISCARDBODY
};

class Entity
{
public:
	int GetTeam();
	bool IsDormant();
	bool IsValid();
	short GetActiveWeapon();
};