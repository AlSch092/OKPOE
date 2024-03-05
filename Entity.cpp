#include "Entity.hpp"
#include "AutoPlayer.hpp"

extern AutoPlayer* g_Robot;

Entity::~Entity()
{
	//clean up any memory here
}

void Entity::Initialize(UINT64 EntityAddress)
{
	if (g_Robot->DebugMode)
	{
		printf("[DEBUG] E::Initialize called.\n");
	}

	if (EntityAddress == NULL)
		return;

	UINT64 Addr = EntityAddress += 8;

	if (Addr != NULL)
	{
		this->Address = Addr;
		this->UniqueID = this->GetUniqueID();
		
		if (this->UniqueID != 0)// && this->UniqueID < 65535)
		{
			wchar_t* filePath = this->GetFilePathFromMemory();

			if (filePath != NULL)
			{
				wcscpy(this->FilePath, filePath);

				this->ComponentListEnd = DereferenceSafe<UINT64>(Addr + (sizeof(UINT64) * 2));
				this->ComponentListAddress = DereferenceSafe<UINT64>(Addr + sizeof(UINT64));

				this->SetComponentLookup(Addr); //sets component count

				if (this->ComponentListAddress > 0)
				{
					this->FillComponentList();

					bool ignored = false;

					for each(wchar_t* str in g_Robot->IgnoredEntities)
					{
						if (wcscmp(str, this->FilePath) == 0)
						{
							ignored = true;
						}
					}

					if (!ignored)
					{
						if (!g_Robot->EntityMsgsSupressed)
						{
							FileIO::Log("[ENTITY] Base Address: %llX\n", Addr - 8);
							wprintf(L"File: %s\n", this->FilePath);
							FileIO::Log("Component List: %llX\n", this->ComponentListAddress);
							FileIO::Log("Number of Components: %d\n", this->ComponentCount);
							FileIO::Log("Component Lookup: %llX\n", this->ComponentLookupAddress);
							FileIO::Log("Id: %d\n", this->UniqueID);
							FileIO::Log("/[ENTITY]\n");
						}
					}
				}
				else
				{
					FileIO::Log("[ERROR] Failed to parse entity: %llX\n", Addr);
				}
			}
		}	
	}
}

void Entity::SetComponentLookup(UINT64 Address)
{
	if (g_Robot->DebugMode)
	{
		printf("[DEBUG] SetComponentLookup called.\n");
	}

	if (Address >= 0)
	{
		UINT64 ComponentLookupAddr = DereferenceSafe<UINT64>(Address);
		ComponentLookupAddr = DereferenceSafe<UINT64>(ComponentLookupAddr + 0x30);

		ComponentCount = DereferenceSafe<UINT32>(ComponentLookupAddr + 0x48);
		this->ComponentCountAddress = ComponentLookupAddr + 0x48;

		ComponentLookupAddr = DereferenceSafe<UINT64>(ComponentLookupAddr + 0x30);

		this->ComponentLookupAddress = ComponentLookupAddr;
	}
}

UINT32 Entity::GetUniqueID()
{
	if (this == nullptr)
		return 0;

	uint32_t id = DereferenceSafe<UINT32>(this->Address + 0x58);
	this->UniqueID = id;

	return id;
}

UINT64 ModuleBase = (UINT64)GetModuleHandle(L"PathOfExile.exe");
bool Entity::AddComponent(UINT64 Address) //badly needs re-writing
{
	UINT64 NamePtr = DereferenceSafe<UINT64>(Address);
	UINT64 StartAddressRange = 0x7FF600000000;
	
	if (ModuleBase)
		StartAddressRange = ModuleBase;

	if (NamePtr > StartAddressRange && NamePtr < 0x7FF7FFFFFFFF)
	{
		if (g_Robot->DebugMode)
		{
			printf("[DEBUG] AddComponent (%llX), namePtr: %llX\n", Address, NamePtr);
		}

		UINT32 Index = DereferenceSafe<UINT32>(Address + sizeof(UINT64));

		if (Index >= 20)
			return false;

		bool duplicate = false;

		if (ComponentList.size() > 0)
		{
			for each (ComponentListNode * CLN in ComponentList)
			{
				if (Index == CLN->Index)
				{
					duplicate = true;
					return false;
				}
			}
		}

		ComponentListNode* CLN = new ComponentListNode();

		char* cNamePtr = DereferenceSafe<char*>(Address);//reinterpret_cast<const char*>(NamePtr);

		if (cNamePtr == NULL)
		{
			delete CLN;
			return false;
		}

		char* innerPtr = DereferenceSafe<char*>((UINT64)cNamePtr);

		if (innerPtr == NULL)
		{
			delete CLN;
			return false;
		}

		if (strnlen_s(cNamePtr, 25) >= 3)
		{
			if (cNamePtr[0] >= 'A' && cNamePtr[0] <= 'Z')
			{
				CLN->Name = cNamePtr; //this is exact crashing line
				CLN->Index = Index;
				CLN->NamePtrAddress = NamePtr;
				CLN->IndexPtr = Address + sizeof(UINT64);

				UINT64 ComponentAddress = (UINT64)(this->ComponentListAddress + (sizeof(uint64_t) * CLN->Index));
				ComponentAddress = DereferenceSafe<UINT64>(ComponentAddress);

				CLN->ComponentAddress = ComponentAddress;

				this->ComponentList.push_back(CLN);

				if (g_Robot->DebugMode)
					printf("[DEBUG] [%d] AddComponent (%llX), %s\n", CLN->Index, CLN->ComponentAddress, CLN->Name.c_str());
					
				return true;
			}
			else
			{
				//printf("AddComponent::NamePtr error 5\n");
				delete CLN;
				return false;
			}
		}
		else
		{
			printf("AddComponent::NamePtr error 3\n");
			delete CLN;
			return false;
		}							
	}
	
	return false;
}

void Entity::FillComponentList()
{
	if (g_Robot->DebugMode)
	{
		printf("[DEBUG] FillComponentList called.\n");
	}

	if (this == nullptr)
		return;

	UINT64 CurrentAddress = this->ComponentLookupAddress; //will be at dwJunk1 on a random index
	int count = 0;
	int stuckCounter = 0;

	while (count < this->ComponentCount)
	{
		if (AddComponent(CurrentAddress))
		{
			CurrentAddress += 0x10;
			count += 1;
		}
		else
		{
			CurrentAddress += 0x8;
		}

		stuckCounter++;

		if (stuckCounter > 50)
			return;
	}
}

void Entity::ClearComponentList() //todo: check for leaked memory
{
	this->ComponentList.clear();
}

UINT64 Entity::GetComponentAddress(string ComponentName)
{
	UINT64 ComponentAddress = NULL;

	for each (ComponentListNode* CLN in ComponentList)
	{
		if (CLN != NULL)
		{
			if (CLN->Index >= 0 && CLN->Index <= 20)
			{
				if (!CLN->Name.empty())
				{
					//if(ComponentName == CLN->Name)
					if (strcmp(ComponentName.c_str(), CLN->Name.c_str()) == 0)	
					{
						if (g_Robot->DebugMode)						
							printf("[DEBUG] GetComponentAddress returned: %llX.\n", CLN->ComponentAddress);
						
						ComponentAddress = (UINT64)(this->ComponentListAddress + (sizeof(uint64_t) * CLN->Index));
						ComponentAddress = DereferenceSafe<UINT64>(ComponentAddress);
					}
				}
			}
		}
	}
	
	return ComponentAddress; //unfound case
}

wchar_t* Entity::GetFilePathFromMemory()
{
	auto arrPath = new wchar_t[512] {0};

	auto PathPtr = ReadPointer<UINT64>(this->Address, 0x08);

	if (PathPtr == NULL) //exception thrown
		return NULL;

	__try
	{
		if (PathPtr != NULL)
			wcscpy_s(arrPath, 512, (const wchar_t*)PathPtr); //this will crash..

		if (arrPath[0] != L'M')
			return NULL;

		return arrPath;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		return NULL;
	}
}

Vector2 Entity::GetVector2()
{
	auto ComponentAddr = this->GetComponentAddress("Positioned");

	if (ComponentAddr == NULL)
	{
		return{ 0, 0 };
	}

	int x = DereferenceSafe<int>(ComponentAddr + Positioned::Offsets::GridPosition); //maybe include postioned and use offsets inthere
	int y = DereferenceSafe<int>(ComponentAddr + Positioned::Offsets::GridPosition + 4);

	return{ x, y };
}

bool Entity::IsTargetable()
{
	auto ComponentAddr = this->GetComponentAddress("Targetable");

	if (ComponentAddr == NULL)
		return false;

	if (ComponentAddr >= 0x0000010000000000) //start of heap, protects vs bad ptrs kinda
	{
		auto Targetable = DereferenceSafe<BYTE>(ComponentAddr + Targetable::TargetableOffset);
		return Targetable;
	}

	return false;
}

bool Entity::IsHovered()
{
	auto ComponentAddr = this->GetComponentAddress("Targetable");

	if (ComponentAddr == NULL)
		return false;

	auto Targetable = DereferenceSafe<BYTE>(ComponentAddr + Targetable::HoveringOffset);
	return Targetable;
}

bool Entity::IsAlive()
{
	auto HP = Life::GetEntityHP(this);
	return (HP > 0) ? true : false;
}

void Entity::PrintNotableEntities(Entity* e)
{
	wchar_t* w = e->GetFilePathFromMemory();
	Vector2 GridLocation = e->GetVector2();

	if (wcsstr(w, L"Unique") != NULL) //make this more portable
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_INTENSITY | FOREGROUND_RED));
		wprintf(L"**UNIQUE CHEST DETECTED**: (%d, %d) Path: %s\n", GridLocation.X, GridLocation.Y, w);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (0 | 15)); // 0 or 15 = 15 (0 / 11111)
	}
	else if (wcsstr(w, L"FossilChest") != NULL)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_INTENSITY | FOREGROUND_RED));
		wprintf(L"**FOSSIL CHEST DETECTED**: (%d, %d) Path: %s\n", GridLocation.X, GridLocation.Y, w);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (0 | 15));
	}
	else if (wcsstr(w, L"Resonator3") != NULL)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_INTENSITY | FOREGROUND_RED));
		wprintf(L"**RESONATOR CACHE DETECTED**: (%d, %d)  Path: %s\n", GridLocation.X, GridLocation.Y, w);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (0 | 15));
	}
	else if (wcsstr(w, L"Resonator4") != NULL)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_INTENSITY | FOREGROUND_RED));
		wprintf(L"**RESONATOR HOARDE!!! DETECTED**: (%d, %d)  Path: %s\n", GridLocation.X, GridLocation.Y, w);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (0 | 15));
	}
	else if (wcsstr(w, L"DelveChests/Resonator") != NULL)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_INTENSITY | FOREGROUND_RED));
		wprintf(L"**RESONATOR Chest!!! DETECTED**: (%d, %d)  Path: %s\n", GridLocation.X, GridLocation.Y, w);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (0 | 15));
	}
	else if (wcsstr(w, L"Divination") != NULL)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_INTENSITY | FOREGROUND_RED));
		wprintf(L"**DIVINATION CHEST DETECTED**: (%d, %d)  Path: %s\n", GridLocation.X, GridLocation.Y, w);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (0 | 15));
	}
	else if (wcsstr(w, L"Divination") != NULL)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_BLUE));
		wprintf(L"**DIVINATION CHEST DETECTED**: (%d, %d)  Path: %s\n", GridLocation.X, GridLocation.Y, w);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (0 | 15));
	}
	else if (wcsstr(w, L"OffPathCurrency") != NULL)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_GREEN));
		wprintf(L"**OFFPATH CURRENCY CHEST DETECTED**: (%d, %d)  Path: %s\n", GridLocation.X, GridLocation.Y, w);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (0 | 15));
	}
	else if (wcsstr(w, L"DynamiteCurrency") != NULL)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_GREEN));
		wprintf(L"**DYNAMITE CURRENCY2 CHEST DETECTED**: (%d, %d)  Path: %s\n", GridLocation.X, GridLocation.Y, w);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (0 | 15));
	}
	else if (wcsstr(w, L"DynamiteCurrency2") != NULL)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_GREEN));
		wprintf(L"**DYNAMITE CURRENCY CHEST DETECTED**: (%d, %d)  Path: %s\n", GridLocation.X, GridLocation.Y, w);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (0 | 15));
	}
	else if (wcsstr(w, L"EternalChest") != NULL)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_GREEN));
		wprintf(L"**DYNAMITE CURRENCY CHEST DETECTED**: (%d, %d)  Path: %s\n", GridLocation.X, GridLocation.Y, w);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (0 | 15));
	}
	else if (wcsstr(w, L"LegionChests/KaruiChest") != NULL)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_RED));
		wprintf(L"**KARUI LEGION CHEST DETECTED**: (%d, %d)  Path: %s\n", GridLocation.X, GridLocation.Y, w);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (0 | 15));
	}
	else if (wcsstr(w, L"LegionChests/EternalEmpireChest") != NULL)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_GREEN));
		wprintf(L"**ETERNAL LEGION CHEST DETECTED**: (%d, %d)  Path: %s\n", GridLocation.X, GridLocation.Y, w);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (0 | 15));
	}
	else if (wcsstr(w, L"LegionChests/VaalChest") != NULL)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_GREEN));
		wprintf(L"**VAAL LEGION CHEST DETECTED**: (%d, %d)  Path: %s\n", GridLocation.X, GridLocation.Y, w);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (0 | 15));
	}
	else if (wcsstr(w, L"LegionChests/TemplarChest") != NULL)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_GREEN));
		wprintf(L"**TEMPLAR LEGION CHEST DETECTED**: (%d, %d)  Path: %s\n", GridLocation.X, GridLocation.Y, w);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (0 | 15));
	}

	delete e;
}

bool Entity::IsCorpse(Entity* e)
{
	return Actor::GetCurrentActionID(e) == 0x0040 ? 1 : 0;
}

GroundItem* Entity::GetInnerItemEntity()
{
	auto ComponentAddr = this->GetComponentAddress("WorldItem");

	if (ComponentAddr == NULL)
	{
		FileIO::Log("Failed to create subobject from WorldItem: Can't find component at %llX", ComponentAddr);
		return NULL;
	}

	UINT64 EntAddr = DereferenceSafe<UINT64>(ComponentAddr + WorldItem::ItemOffset);

	if (EntAddr != NULL)
	{
		auto e = new GroundItem(EntAddr); //ID will be invalid, need to use parentEntity
		
		if (e == NULL)
		{
			printf("[OKPOE LOG]GetSubObjectEntity->e = NULL!\n ");
			return NULL;
		}

		return e;
	}

	return NULL;
}