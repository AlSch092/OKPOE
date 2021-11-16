#include "Entity.hpp"
#include "AutoPlayer.hpp"

extern AutoPlayer* Robot;

void Entity::Initialize(UINT64 EntityAddress)
{
	UINT64 Addr = EntityAddress += 8;
	
	if (Addr != NULL)
	{
		this->Address = Addr;
		this->UniqueID = this->GetUniqueID();
		this->FilePath = this->GetFilePathFromMemory();

		this->PositionedComponentAddress = DereferenceSafe<UINT64>(EntityAddress + 0x68); //
		
		this->ComponentListEnd = DereferenceSafe<UINT64>(Addr + (sizeof(UINT64) * 2));
		this->ComponentListAddress = DereferenceSafe<UINT64>(Addr + sizeof(UINT64));
		
		this->SetComponentLookup(Addr);
		
		if (this->ComponentListAddress > 0)
		{
			if (Robot->WritingToFile) //fix this!!
			{
				FileIO::FileLog("Entity Address: %llX", this->Address);
			
				if (Robot->LoggingComponents)
				{
					for each(NewComponentListNode* CLN in this->ComponentList)
					{
						if (CLN->NamePtrAddress != NULL)
						{
							if (CLN->IndexPtr != NULL)
							{
								UINT64 CompAddr = this->ComponentListAddress + (8 * CLN->Index);
								FileIO::FileLog("Component %s: %d (%llX)\n", CLN->NamePtrAddress, CLN->Index, CompAddr);
							}
							
						}
							
					}
				}
			}
			else
			{
				bool ignored = false;

				for each(wchar_t* str in Robot->IgnoredEntities)
				{
					if (wcscmp(str, this->FilePath.c_str()) == 0)
					{
						ignored = true;
					}
				}

				if (!ignored)
				{
					if (!Robot->EntityMsgsSupressed)
					{
						int X = this->GetVector2().X;
						int Y = this->GetVector2().Y;

						FileIO::Log("=== Entity Created === \n");
						FileIO::Log("Base Address: %llX\n", Addr);
						FileIO::WLog(L"File: %s\n", this->FilePath.c_str());
						FileIO::Log("Component List: %llX\n", this->ComponentListAddress);
						FileIO::Log("Number of Components: %d\n", this->ComponentCount);
						FileIO::Log("Component Lookup: %llX\n", this->ComponentLookupAddress);
						FileIO::Log("Id: %d\n", this->UniqueID);
						FileIO::Log("Positioned: %llX\n", this->PositionedComponentAddress);
						FileIO::Log("Co-ords: %d, %d\n", X, Y);

						if (Robot->LoggingComponents)
						{
							for each(NewComponentListNode* CLN in this->ComponentList)
							{
								if (CLN->NamePtrAddress != NULL)
								{
									if (CLN->IndexPtr != NULL)
									{
										UINT64 CompAddr = this->ComponentListAddress + (8 * CLN->Index);
										FileIO::FileLog("Component %s: %d (%llX)\n", CLN->NamePtrAddress, CLN->Index, CompAddr);
									}
								}

							}

						}

						
						if (wcsstr(this->FilePath.c_str(), L"Metadata/Items/") != NULL || wcsstr(this->FilePath.c_str(), L"Metadata/Monsters/") != NULL || wcsstr(this->FilePath.c_str(), L"Metadata/Characters/") != NULL || wcsstr(this->FilePath.c_str(), L"Metadata/Chests/") != NULL || wcsstr(this->FilePath.c_str(), L"Metadata/MiscellaneousObjects/Expedition/") != NULL || wcscmp(this->FilePath.c_str(), L"Metadata/MiscellaneousObjects/Waypoint") == 0)
						{						
							Robot->EntityList.push_back(this); //push entities we want to save or may need for scripting
						}

						FileIO::Log("====================== \n");

					}					
				}

			}
		}
	}
}

void Entity::SetComponentLookup(UINT64 Address) //broken...
{
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
	UINT64 IDAddress = this->Address + 0x58;

	if (IDAddress != 0)
	{
		UINT32 ID = DereferenceSafe<UINT32>(IDAddress);

		if (ID != NULL)
			return ID;
	}

	return 0;
}

void Entity::FillComponentList() //most common cause of crashing at 3.16
{
	UINT64 CurrentAddress = this->ComponentLookupAddress; //will be at dwJunk1 on a random index
	CurrentAddress += 0x08;
	int count = 0;

	if (this->ComponentCount == 0)
		return;

	while (count < this->ComponentCount)
	{
		char ComponentName[256] = { 0 };

		UINT64 JunkRead = DereferenceSafe<UINT64>(CurrentAddress);

		if (JunkRead > 0x7FF600000000 && JunkRead < 0x7FF7FFFFFFFF)
		{	
			__try
			{
				NewComponentListNode* CLN = new NewComponentListNode();

				CLN->NamePtrAddress = CurrentAddress;

				CurrentAddress += 0x08;

				CLN->IndexPtr = CurrentAddress;

				CurrentAddress += 0x08;

				CLN->NamePtrAddress = DereferenceSafe<UINT64>(CLN->NamePtrAddress);
				CLN->Index = DereferenceSafe<UINT32>(CLN->IndexPtr);

				//FileIO::Log("[DEBUG] Name Address: %llX\n", CLN->NamePtrAddress);
				//FileIO::Log("[DEBUG] Index Address: %llX\n", CLN->IndexPtr);
				//FileIO::Log("[DEBUG] Index: %d\n", CLN->Index);

				if (DereferenceSafe<UINT64>(CLN->IndexPtr) != NULL)
				{
					if (CLN->NamePtrAddress >= 0x7FF600000000 && CLN->NamePtrAddress < 0x7FF7FFFFFFFF)
					{
						if (CLN->Index >= 0 && CLN->Index < 25)
						{
							strcpy_s(CLN->Name, 50, (char*)CLN->NamePtrAddress);

							this->ComponentList.push_back(CLN);
							count += 1;
						}
					}
				}

			}
			__except (EXCEPTION_EXECUTE_HANDLER) { continue; }
	
		}
		else
		{		
			//printf("Component read ..\n");
			CurrentAddress += sizeof(UINT64);
			continue;
		}
		
	}
}

void Entity::ClearComponentList()
{
	//no mem leaks to worry about iirc. need double check on CLN's
	this->ComponentList.clear();
}


UINT64 Entity::GetComponentAddress(char* ComponentName)
{
	for each (NewComponentListNode* CLN in this->ComponentList)
	{
		if (CLN->Index >= 0 && CLN->Index <= this->ComponentCount)
		{
			if (strlen(CLN->Name) > 0)
			{
				if (strncmp((const char*)CLN->Name, ComponentName, strlen(ComponentName) + 1) == 0)
				{
					UINT64 ComponentAddress = (UINT64)(this->ComponentListAddress + (sizeof(uint64_t) * CLN->Index));
					ComponentAddress = DereferenceSafe<UINT64>(ComponentAddress);
					return ComponentAddress;
				}
			}

		}
	}

	return 0; //unfound case
}



std::wstring Entity::GetFilePathFromMemory()
{
	wchar_t arrPath[128];

	UINT64 PathPtr = ReadPointer<UINT64>(this->Address, 0x08);

	if (PathPtr ==  NULL) //exception thrown
		return NULL;

	try
	{
		wcscpy(arrPath, (const wchar_t*)PathPtr); //this will crash..
		this->FilePath = std::wstring(arrPath);
	}
	catch (exception e)
	{
		FileIO::Log("Could not get entity file path.\n");
	}

	return arrPath;
}

bool Entity::IsSummoned() //need a better way like check if PlayerControlled is a component
{
	std::wstring Path = this->FilePath;

	if (wcsstr(Path.c_str(), L"FireElemental") != NULL) //too generic...
		return true;
	else if (wcsstr(Path.c_str(), L"Totem") != NULL)
		return true;
	else if (wcsstr(Path.c_str(), L"Metadata/Monsters/Totems/MortarTotem") != NULL)
		return true;
	else if (wcsstr(Path.c_str(), L"RaisedZombieStandard") != NULL)
		return true;
	else if (wcsstr(Path.c_str(), L"RaisedSpectreStandard") != NULL)
		return true;
	return false;
}

Entity* Entity::GetSubObjectEntity()
{
	UINT64 ComponentAddr = this->GetComponentAddress("WorldItem");

	if (ComponentAddr == NULL)
	{
		FileIO::Log("Failed to create subobject from WorldItem: Can't find component at %llX", ComponentAddr);
		return NULL;
	}

	ComponentAddr = ComponentAddr + 0x28;// +0x28;
	ComponentAddr = DereferenceSafe<UINT64>(ComponentAddr);

	Entity* e = new Entity(ComponentAddr);
	return e;
}

Vector2 Entity::GetVector2()
{
	UINT64 ComponentAddr = this->PositionedComponentAddress;
	
	if (ComponentAddr == NULL)
	{
		return{ 0, 0 };
	}

	int x = DereferenceSafe<int>(ComponentAddr + 0x1E8); //maybe include postioned and use offsets inthere
	int y = DereferenceSafe<int>(ComponentAddr + 0x1EC);
	
	return {x,y};
}

bool Entity::IsTargetable() //0x50 = isHovering
{
	UINT64 ComponentAddr = this->GetComponentAddress("Targetable");

	if (ComponentAddr == NULL)
		return false;

	BYTE Targetable = DereferenceSafe<BYTE>(ComponentAddr + 0x48);
	return Targetable;
}

bool Entity::IsHovered() //0x50 = isHovering
{
	UINT64 ComponentAddr = this->GetComponentAddress("Targetable");

	if (ComponentAddr == NULL)
		return false;

	BYTE Targetable = DereferenceSafe<BYTE>(ComponentAddr + 0x50);
	return Targetable;
}

bool Entity::IsAlive()
{
	UINT HP = Life::GetEntityHP(this);
	return (HP > 0) ? true : false;
}




void Entity::PrintNotableEntities(Entity* e)
{
	std::wstring w = e->GetFilePathFromMemory();
	Vector2 GridLocation = e->GetVector2();

	if (wcsstr(w.c_str(), L"Unique") != NULL) //make this more portable
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_INTENSITY | FOREGROUND_RED));
		wprintf(L"**UNIQUE CHEST DETECTED**: (%d, %d) Path: %s\n", GridLocation.X, GridLocation.Y, w.c_str());
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (0 | 15)); // 0 or 15 = 15 (0 / 11111)
	}
	else if (wcsstr(w.c_str(), L"FossilChest") != NULL)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_INTENSITY | FOREGROUND_RED));
		wprintf(L"**FOSSIL CHEST DETECTED**: (%d, %d) Path: %s\n", GridLocation.X, GridLocation.Y, w.c_str());
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (0 | 15));
	}
	else if (wcsstr(w.c_str(), L"Resonator3") != NULL)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_INTENSITY | FOREGROUND_RED));
		wprintf(L"**RESONATOR CACHE DETECTED**: (%d, %d)  Path: %s\n", GridLocation.X, GridLocation.Y, w.c_str());
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (0 | 15));
	}
	else if (wcsstr(w.c_str(), L"Resonator4") != NULL)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_INTENSITY | FOREGROUND_RED));
		wprintf(L"**RESONATOR HOARDE!!! DETECTED**: (%d, %d)  Path: %s\n", GridLocation.X, GridLocation.Y, w.c_str());
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (0 | 15));
	}
	else if (wcsstr(w.c_str(), L"Divination") != NULL)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_INTENSITY | FOREGROUND_RED));
		wprintf(L"**DIVINATION CHEST DETECTED**: (%d, %d)  Path: %s\n", GridLocation.X, GridLocation.Y, w.c_str());
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (0 | 15));
	}
	else if (wcsstr(w.c_str(), L"Divination") != NULL)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_BLUE));
		wprintf(L"**DIVINATION CHEST DETECTED**: (%d, %d)  Path: %s\n", GridLocation.X, GridLocation.Y, w.c_str());
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (0 | 15));
	}
	else if (wcsstr(w.c_str(), L"OffPathCurrency") != NULL)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_GREEN));
		wprintf(L"**OFFPATH CURRENCY CHEST DETECTED**: (%d, %d)  Path: %s\n", GridLocation.X, GridLocation.Y, w.c_str());
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (0 | 15));
	}
	else if (wcsstr(w.c_str(), L"DynamiteCurrency") != NULL)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_GREEN));
		wprintf(L"**DYNAMITE CURRENCY2 CHEST DETECTED**: (%d, %d)  Path: %s\n", GridLocation.X, GridLocation.Y, w.c_str());
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (0 | 15));
	}
	else if (wcsstr(w.c_str(), L"DynamiteCurrency2") != NULL)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_GREEN));
		wprintf(L"**DYNAMITE CURRENCY CHEST DETECTED**: (%d, %d)  Path: %s\n", GridLocation.X, GridLocation.Y, w.c_str());
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (0 | 15));
	}
	else if (wcsstr(w.c_str(), L"EternalChest") != NULL)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_GREEN));
		wprintf(L"**DYNAMITE CURRENCY CHEST DETECTED**: (%d, %d)  Path: %s\n", GridLocation.X, GridLocation.Y, w.c_str());
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (0 | 15));
	}
	else if (wcsstr(w.c_str(), L"LegionChests/KaruiChest") != NULL)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_RED));
		wprintf(L"**KARUI LEGION CHEST DETECTED**: (%d, %d)  Path: %s\n", GridLocation.X, GridLocation.Y, w.c_str());
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (0 | 15));
	}
	else if (wcsstr(w.c_str(), L"LegionChests/EternalEmpireChest") != NULL)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_GREEN));
		wprintf(L"**ETERNAL LEGION CHEST DETECTED**: (%d, %d)  Path: %s\n", GridLocation.X, GridLocation.Y, w.c_str());
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (0 | 15));
	}
	else if (wcsstr(w.c_str(), L"LegionChests/VaalChest") != NULL)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_GREEN));
		wprintf(L"**VAAL LEGION CHEST DETECTED**: (%d, %d)  Path: %s\n", GridLocation.X, GridLocation.Y, w.c_str());
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (0 | 15));
	}
	else if (wcsstr(w.c_str(), L"LegionChests/TemplarChest") != NULL)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_GREEN));
		wprintf(L"**TEMPLAR LEGION CHEST DETECTED**: (%d, %d)  Path: %s\n", GridLocation.X, GridLocation.Y, w.c_str());
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (0 | 15));
	}
}

