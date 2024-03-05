#pragma once
#include <list>
#include "Structures.hpp"
#include "Components.hpp"
#include "Pointer.hpp"
#include "Offsets.hpp"


class GroundItem;

class Entity
{
	enum CreatureType
	{
		Player = 13,
		Minion = 1,
		Normal = 2,
		Magic = 4,
		Rare = 7,
		Unique = 10
	};

public:

	Entity() {}

	Entity(UINT64 Ptr)
	{
		Initialize(Ptr);
	}
	
	~Entity();

	//Vars
	UINT64 Address;

	UINT64 ComponentListAddress;
	UINT64 ComponentLookupAddress;
	UINT64 ComponentListEnd;

	UINT32 ComponentCount;
	UINT64 ComponentCountAddress;

	std::list<ComponentListNode*> ComponentList = std::list<ComponentListNode*>(); //need to manage the memory for list members?

	UINT64 PositionedComponentAddress; //+0x80 from base addr..

	//std::wstring FilePath;
	wchar_t FilePath[512];
	
	UINT32 UniqueID;

	//Routines
	void Initialize(UINT64 EntityAddress);
	void Destroy();

	UINT32 GetUniqueID(); //0x60

	void SetComponentLookup(UINT64 Address);
	void FillComponentList();
	bool AddComponent(UINT64 Address);
	void ClearComponentList();
	UINT64 GetComponentAddress(std::string ComponentName);
	
	wchar_t* GetFilePathFromMemory();
	
	GroundItem* GetInnerItemEntity();

	Vector2 GetVector2();

	bool IsAlive();
	bool IsTargetable();
	bool IsHovered();
	static bool IsCorpse(Entity* e);

	void Action(UINT64 LocalState, short SkillId, __in_opt Entity* SelectedEntity, Vector2 AtPosition); //; UINT64 State, SHORT SkillID, r8 optional_entity, r9 Ptr Vector2

	static void PrintNotableEntities(Entity* e);

	bool IsSummoned();

	int GetComponents();

	int DistanceAwayFromLocalPlayer; //needs better solution
};

struct EntityListNode
{
	UINT64 vTableAddr;
	Entity* Ent;
	std::list<ComponentListNode*> ComponentList;
};