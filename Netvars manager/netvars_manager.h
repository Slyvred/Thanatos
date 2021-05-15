#pragma once
#include <iostream>
#include "..\SDK\VirtualMethod.h"

// https://guidedhacking.com

class RecvProp;

class RecvTable
{
public:
	RecvProp*	m_pProps;
	int			m_nProps;
	void*		m_pDecoder;
	const char* m_pNetTableName;
	bool		m_bInitialized;
	bool		m_bInMainList;
};

class RecvProp
{
public:

	const char* m_pVarName;
	void*		m_RecvType;
	int			m_Flags;
	int			m_StringBufferSize;
	bool		m_bInsideArray;
	const void* m_pExtraData;
	RecvProp*	m_pArrayProp;
	void*		m_ArrayLengthProxy;
	void*		m_ProxyFn;
	void*		m_DataTableProxyFn;	// For RDT_DataTable.
	RecvTable*	m_pDataTable;		// For RDT_DataTable.
	int			m_Offset;
	int			m_ElementStride;
	int			m_nElements;
	const char* m_pParentArrayPropName;
};

class IClientNetworkable;

typedef IClientNetworkable* (*CreateClientClassFn)(int entnum, int serialNum);
typedef IClientNetworkable* (*CreateEventFn)();

class ClientClass
{
public:
	//CreateClientClassFn m_pCreateFn;
	std::add_pointer_t<void* __cdecl(int, int)> m_pCreateFn;
	CreateEventFn       m_pCreateEventFn;	// Only called for event objects.
	const char*			m_pNetworkName;
	RecvTable*			m_pRecvTable;
	ClientClass*		m_pNext;
	int					m_ClassID;	// Managed by the engine.
};

intptr_t GetOffset(RecvTable* table, const char* tableName, const char* netvarName);
intptr_t GetNetvarOffset(const char* tableName, const char* netvarName, ClientClass* clientClass);