#pragma once
#include <list>
#include "Structures.hpp"
#include "Components.hpp"
#include "Pointer.hpp"
#include "Offsets.hpp"


class Entity
{
public:

	Entity() {}

	Entity(UINT64 Ptr)
	{
		this->Initialize(Ptr);
	}

	//Vars
	UINT64 Address;
	UINT64 PathAddress;
	UINT64 ComponentListAddress;
	UINT64 ComponentLookupAddress;
	UINT64 ComponentListEnd;
	UINT32 ComponentCount;
	UINT64 ComponentCountAddress;
	std::list<NewComponentListNode*> ComponentList;

	UINT64 PositionedComponentAddress; //+0x70 from base addr..

	std::wstring FilePath;
	Vector2 Position;
	Vector3 Location;
	UINT32 UniqueID;

	BOOL CanTarget; //these vars mayvbe not needed since we can look up when needed with mem offset

	//Routines
	void Initialize(UINT64 EntityAddress);

	UINT32 GetUniqueID();

	void SetComponentLookup(UINT64 Address);
	void FillComponentList();
	void ClearComponentList();
	UINT64 GetComponentAddress(char* ComponentName);
	
	std::wstring GetFilePathFromMemory();
	Entity* GetSubObjectEntity();

	Vector2 GetVector2();

	bool IsAlive();
	bool IsTargetable();
	bool IsHovered();

	void Action(UINT64 LocalState, short SkillId, __in_opt Entity* SelectedEntity, Vector2 AtPosition); //; UINT64 State, SHORT SkillID, r8 optional_entity, r9 Ptr Vector2

	static void PrintNotableEntities(Entity* e);

	bool IsSummoned();
};

struct EntityListNode
{
	UINT64 vTableAddr;
	Entity* Ent;
	std::list<ComponentListNode*> ComponentList;
};