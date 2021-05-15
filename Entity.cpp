#include "Entity.h"
#include "offsets.h"
#include "Tanatos.h"
extern Tanatos tanatos;

int Entity::GetTeam()
{
	return *(int*)(this + netvars::m_iTeamNum);
}

bool Entity::IsDormant()
{
	return *(bool*)(this + signatures::m_bDormant);
}

bool Entity::IsValid()
{
	if (this == nullptr || *(LifeState*)(this + netvars::m_lifeState) == LifeState::LIFE_DEAD || this->IsDormant()) return false;
	else return true;
}

short Entity::GetActiveWeapon()
{
	intptr_t activeWeapon = *(intptr_t*)(this + netvars::m_hActiveWeapon);
	activeWeapon = (intptr_t)tanatos.ClientEntityList->GetClientEntityFromHandle(activeWeapon);

	return activeWeapon ? *(short*)(activeWeapon + netvars::m_iItemDefinitionIndex) : NULL;
}
