#pragma once
#include "VirtualMethod.h"

enum DataUpdateType_t
{
	DATA_UPDATE_CREATED = 0,
	DATA_UPDATE_ENTERED_PVS,
	DATA_UPDATE_DATATABLE_CHANGED,
	DATA_UPDATE_LEFT_PVS,
	DATA_UPDATE_DESTROYED,
};

class IClientNetworkable
{
public:
	virtual void* GetIClientUnknown() = 0;
	virtual void			Release() = 0;
	virtual ClientClass* GetClientClass() = 0;
	virtual void			NotifyShouldTransmit(void* state) = 0;
	virtual void			OnPreDataChanged(DataUpdateType_t updateType) = 0;
	virtual void			OnDataChanged(DataUpdateType_t updateType) = 0;
	virtual void			PreDataUpdate(DataUpdateType_t updateType) = 0;
	virtual void			PostDataUpdate(DataUpdateType_t updateType) = 0;
	virtual bool			IsDormant(void) = 0;
};

class IClientEntityList
{
public:
    VIRTUAL_METHOD(IClientNetworkable*, GetClientNetworkable, 0, (int entnum), (this, entnum))
    VIRTUAL_METHOD(void*, GetClientEntity, 3, (int index), (this, index))
    VIRTUAL_METHOD(void*, GetClientEntityFromHandle, 4, (int hEnt), (this, hEnt))
    VIRTUAL_METHOD(int, GetHighestEntityIndex, 6, (), (this))
};