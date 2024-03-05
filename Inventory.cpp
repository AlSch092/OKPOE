#include "Inventory.hpp"

extern AutoPlayer* g_Robot;
extern NetLogger* g_ProtectionServer;

Item* NormalInventory::GetInventoryItem(UINT64 ElementAddr)
{
	Item* item = new Item();
	
	if (item != NULL)
	{
		UINT64 CellX = DereferenceSafe<UINT64>(ElementAddr + Inventory::CellXOffset);
		UINT64 CellY = DereferenceSafe<UINT64>(ElementAddr + Inventory::CellYOffset);
		UINT64 EntityAddr = DereferenceSafe<UINT64>(ElementAddr + Inventory::EntityOffset);
		UINT64 Height = DereferenceSafe<UINT64>(ElementAddr + Inventory::CellHeightOffset);
		UINT64 Width = DereferenceSafe<UINT64>(ElementAddr + Inventory::CellWidthOffset);

		if (EntityAddr != NULL)
		{
			item->CellX = DereferenceSafe<UINT32>(CellX);
			item->CellY = DereferenceSafe<UINT32>(CellY);
			item->Height = DereferenceSafe<UINT32>(Height);
			item->Width = DereferenceSafe<UINT32>(Width);
	
			item->ItemEnt = new Entity(EntityAddr);
		}
	}

	return item;
}

bool NormalInventory::isInventoryFull()
{
	bool full = false;
	int CellsOccupied = 0;

	g_Robot->NormalInv->Items = g_Robot->NormalInv->GetInventoryItems();

	for each(Item* i in g_Robot->NormalInv->Items)
	{
		int x = i->CellX; //check these offsets
		int y = i->CellY;
		int width = i->Width;
		int height = i->Height;

		int nCells = width * height;

		CellsOccupied += nCells;

		if (g_Robot->DebugMode)
		{
			printf("Cell taken by item (%s): %d\n", i->FullName.c_str(), nCells);
		}
	}

	printf("Cells occupied: %d\n", CellsOccupied);

	if (CellsOccupied == 60)
		return true;

	return false;
}

std::list<Item*> NormalInventory::GetInventoryItems()
{
	UINT64 poeBase = (UINT64)GetModuleHandleA(NULL);
	UINT64 Ptr = DereferenceSafe<UINT64>(poeBase + g_ProtectionServer->Offsets[8]);
	std::list<Item*> itms;

	if (Ptr != NULL)
	{
		UINT64 nextAddr = DereferenceSafe<UINT64>(Ptr + Inventory::NormalInvOffset); //0x158 -> flasks list

			if (nextAddr != NULL)
			{
				//we are now at the base inventory element.
				UINT64 ChildElementList = DereferenceSafe<UINT64>(nextAddr + Offsets::Element::ChildsOffset);
				UINT64 ChildElementEnd = DereferenceSafe<UINT64>(nextAddr + Offsets::Element::ChildEndOffset);

				if (ChildElementEnd < ChildElementList)
				{
					printf("ChildElementList was less than end.\n");
					return itms;
				}

				INT nElements = (ChildElementEnd - ChildElementList) / sizeof(UINT64);

				if (g_Robot->DebugMode)
					printf("nElements: %d, Inventory base: %llX, childList: %llX, end: %llX \n", nElements, nextAddr, ChildElementList, ChildElementEnd);	

				for (int i = 1; i < nElements; i++) //first one has no entity
				{
					UINT64 ChildElement = DereferenceSafe<UINT64>(ChildElementList + (i * sizeof(UINT64)));

					if (g_Robot->DebugMode)
						printf("ChildElement at: %llX\n", ChildElement);

					if (ChildElement != NULL) //
					{
						UINT64 EntityAddr = DereferenceSafe<UINT64>(ChildElement + Inventory::EntityOffset);

						if (EntityAddr != NULL) //&& (EntityAddr > 0x010000000000 && EntityAddr < 0x050000000000))
						{
							int inventoryX = DereferenceSafe<int>(ChildElement + Inventory::CellXOffset);
							int inventoryY = DereferenceSafe<int>(ChildElement + Inventory::CellYOffset);

							int sizeX = DereferenceSafe<int>(ChildElement + Inventory::CellWidthOffset);
							int sizeY = DereferenceSafe<int>(ChildElement + Inventory::CellHeightOffset);

							sizeX = 1;
							sizeY = 1;

							if (sizeX > 0 && sizeY > 0)
							{
								Item* im = new Item();

								im->CellX = inventoryX;
								im->CellY = inventoryY;
								im->Height = sizeY;
								im->Width = sizeX;
								im->StashPage = 0;
								im->MemoryAddress = ChildElement;
								
								im->ItemEnt = new Entity(EntityAddr);
								im->InventoryEntityId = DereferenceSafe<UINT32>(ChildElement + Inventory::EntityIdOffset);

								if (im->ItemEnt->GetComponentAddress("Mods") > 0)
								{
									std::wstring namePtr = Mods::GetUniqueName(im->ItemEnt);
									wprintf(L"Item Unique Name: %s\n", namePtr.c_str());
									im->UniqueName = std::wstring(namePtr);
								}

								if (im->ItemEnt->GetComponentAddress("Base") != NULL)
								{
									wstring name = Base::GetBaseName(im->ItemEnt);

									if (!name.empty())
									{
										im->BaseName = wstring(name);
										wprintf(L"Base name: %s\n", name.c_str());
									}
								}

								if (im->ItemEnt->GetComponentAddress("Stack") > NULL)
								{
									im->stackSize = Stack::GetStackSize(im->ItemEnt);
									printf("Stack size: %d\n", im->stackSize);
								}
								else
								{
									im->stackSize = 1;
									printf("Stack size: %d\n", im->stackSize);
								}

								if (!im->BaseName.empty())
								{
									if (!im->UniqueName.empty())
									{
										im->FullName = im->UniqueName + L" " + im->BaseName;
									}
									else
									{
										im->FullName = im->BaseName;
									}
								}
								
								itms.push_back(im);

								if (g_Robot->DebugMode)
									printf("\tCell %d,%d: Child Element at: %llX (Entity %llX)\n", inventoryX, inventoryY, ChildElement, EntityAddr);
							}
						}
					}
				}
		}
	}

	return itms;
}

std::list<Item*> NormalInventory::GetInventoryItems(uint64_t start_offset)
{
	UINT64 poeBase = (UINT64)GetModuleHandleA(NULL);
	UINT64 Ptr = DereferenceSafe<UINT64>(poeBase + g_ProtectionServer->Offsets[8]);
	
	std::list<Item*> itms;

	if (Ptr == NULL)
		return itms;

	UINT64 nextAddr = DereferenceSafe<UINT64>(Ptr + start_offset); //0x158 -> flasks list

	if (nextAddr == NULL)
		return itms;

	//we are now at the base inventory element.
	UINT64 ChildElementList = DereferenceSafe<UINT64>(nextAddr + Offsets::Element::ChildsOffset);
	UINT64 ChildElementEnd = DereferenceSafe<UINT64>(nextAddr + Offsets::Element::ChildEndOffset);

	INT nElements = (ChildElementEnd - ChildElementList) / sizeof(UINT64);

	if (g_Robot->DebugMode)
		printf("nElements: %d, Inventory base: %llX, childList: %llX, end: %llX \n", nElements, nextAddr, ChildElementList, ChildElementEnd);

	for (int i = 1; i < nElements; i++) //first one has no entity
	{
		UINT64 ChildElement = DereferenceSafe<UINT64>(ChildElementList + (i * sizeof(UINT64)));

		if (g_Robot->DebugMode)
			printf("ChildElement at: %llX\n", ChildElement);

		if (ChildElement != NULL) //
		{
			UINT64 EntityAddr = DereferenceSafe<UINT64>(ChildElement + Inventory::EntityOffset);

			printf("Entity at: %llX\n", EntityAddr);

			if (EntityAddr != NULL) //&& (EntityAddr > 0x010000000000 && EntityAddr < 0x050000000000))
			{
				int inventoryX = DereferenceSafe<int>(ChildElement + Inventory::CellXOffset);
				int inventoryY = DereferenceSafe<int>(ChildElement + Inventory::CellYOffset);

				int sizeX = DereferenceSafe<int>(ChildElement + Inventory::CellWidthOffset);
				int sizeY = DereferenceSafe<int>(ChildElement + Inventory::CellHeightOffset);

				sizeX = 1; sizeY = 1;

				if (sizeX > 0 && sizeY > 0)
				{
					Item* im = new Item();
					im->CellX = inventoryX;
					im->CellY = inventoryY;
					im->Height = sizeY;
					im->Width = sizeX;
					im->StashPage = 0;
					im->MemoryAddress = ChildElement;
					im->ItemEnt = new Entity(EntityAddr);
					im->InventoryEntityId = DereferenceSafe<UINT32>(ChildElement + Inventory::EntityIdOffset);

					if (im->ItemEnt->GetComponentAddress("Mods") > 0) //todo: own routine
					{
						std::wstring namePtr = Mods::GetUniqueName(im->ItemEnt);
						wprintf(L"Item Unique Name: %s\n", namePtr.c_str());
						im->UniqueName = std::wstring(namePtr);
					}

					if (im->ItemEnt->GetComponentAddress("Base") != NULL)
					{
						wstring name = Base::GetBaseName(im->ItemEnt);

						if (!name.empty())
						{
							im->BaseName = wstring(name);
							wprintf(L"Base name: %s\n", name.c_str());
						}
					}

					if (im->ItemEnt->GetComponentAddress("Stack") > NULL)
					{
						im->stackSize = Stack::GetStackSize(im->ItemEnt);
						printf("Stack size: %d\n", im->stackSize);
					}
					else
					{
						im->stackSize = 1;
						printf("Stack size: %d\n", im->stackSize);
					}

					if (!im->BaseName.empty())
					{
						if (!im->UniqueName.empty())
						{
							im->FullName = im->UniqueName + L" " + im->BaseName;
						}
						else
						{
							im->FullName = im->BaseName;
						}
					}

					itms.push_back(im);

					if (g_Robot->DebugMode)
						printf("\tCell %d,%d: Child Element at: %llX (Entity %llX)\n", inventoryX, inventoryY, ChildElement, EntityAddr);
				}
			}
		}
	}
		
	return itms;
}


std::list<Item*> CurrencyInventory::GetInventoryItems()
{
	std::list<Item*> itms;
	UINT64 poeBase = (UINT64)GetModuleHandleA(NULL);
	UINT64 Ptr = DereferenceSafe<UINT64>(poeBase + g_ProtectionServer->Offsets[8]);

	if (Ptr == NULL)
		return itms;

	UINT64 nextAddr = DereferenceSafe<UINT64>(Ptr + Inventory::CurrencyTabOffset);  

	if (nextAddr == NULL)
		return itms;

	nextAddr = DereferenceSafe<UINT64>(nextAddr + 0x40); //TODO: turn these magic numbers into declared offsets!

	if (nextAddr == NULL)
		return itms;

	nextAddr = DereferenceSafe<UINT64>(nextAddr + 0x08);
	nextAddr = DereferenceSafe<UINT64>(nextAddr + 0x50);
				
	//we are now at the base inventory element.
	UINT64 ChildElementList = DereferenceSafe<UINT64>(nextAddr + Offsets::Element::ChildsOffset);
	UINT64 ChildElementEnd = DereferenceSafe<UINT64>(nextAddr + Offsets::Element::ChildEndOffset);

	INT nElements = (ChildElementEnd - ChildElementList) / sizeof(UINT64);

	if (g_Robot->DebugMode)
		printf("nElements: %d, Inventory base: %llX, childList: %llX, end: %llX \n", nElements, nextAddr, ChildElementList, ChildElementEnd);

	if (nElements <= 1)
		return itms;

	for (int i = 0; i < nElements; i++) //TODO: turn this into its own routine
	{
		UINT64 ChildElement = DereferenceSafe<UINT64>(ChildElementList + (i * sizeof(UINT64)));

		if (ChildElement != NULL) //
		{
			UINT64 subChildElementList = DereferenceSafe<UINT64>(ChildElement + Offsets::Element::ChildsOffset);
			UINT64 subChildElementListEnd = DereferenceSafe<UINT64>(ChildElement + Offsets::Element::ChildEndOffset);

			INT subElements = (subChildElementListEnd - subChildElementList) / sizeof(UINT64);

			if (subElements > 0 && subElements <= 2)
			{
				UINT64 ChildChildElement = DereferenceSafe<UINT64>(subChildElementList + sizeof(UINT64));

				if (ChildChildElement != NULL)
				{
					UINT64 EntityAddr = DereferenceSafe<UINT64>(ChildChildElement + Inventory::EntityOffset);

					if (EntityAddr != NULL && (EntityAddr > 0x010000000000 && EntityAddr < 0x040000000000))
					{
						int inventoryX = DereferenceSafe<int>(ChildChildElement + Inventory::CellXOffset);
						int inventoryY = DereferenceSafe<int>(ChildChildElement + Inventory::CellYOffset);

						int sizeX = DereferenceSafe<int>(ChildChildElement + Inventory::CellWidthOffset);
						int sizeY = DereferenceSafe<int>(ChildChildElement + Inventory::CellHeightOffset);

						if (sizeX > 0 && sizeY > 0)
						{
							Item* im = new Item();
							im->CellX = inventoryX;
							im->CellY = inventoryY;
							im->Height = sizeY;
							im->Width = sizeX;
							im->StashPage = 0;
							im->MemoryAddress = ChildChildElement;
							im->ItemEnt = new Entity(EntityAddr);
										
							im->InventoryEntityId = DereferenceSafe<UINT32>(ChildChildElement + Inventory::EntityIdOffset);

							if (im->ItemEnt->GetComponentAddress("Base") != NULL)
							{
								wstring name = Base::GetBaseName(im->ItemEnt);

								if (name.size() > 0)
								{
									im->BaseName = wstring(name);
									wprintf(L"Base name: %s\n", name.c_str());
								}

								wstring price = Base::GetPublicPrice(im->ItemEnt);

								if (price.size() > 0)
								{
									im->PriceTag = wstring(price);
									wprintf(L"Price Tag: %s\n", price.c_str());
								}
							}
											
							if (im->ItemEnt->GetComponentAddress("Stack") > NULL) //TODO: write function to do all this stuff as its re-used above too
							{
								im->stackSize = Stack::GetStackSize(im->ItemEnt);
								printf("Stack size: %d\n", im->stackSize);
							}

							if (im->ItemEnt->GetComponentAddress("Mods") > 0)
							{
								std::wstring namePtr = Mods::GetUniqueName(im->ItemEnt);
								if (namePtr.size() > 0)
								{
									wprintf(L"Item Unique Name: %s\n", namePtr.c_str());
									im->UniqueName = std::wstring(namePtr);
								}
								else
									printf("Failed to get item unique name!!!\n");
								
							}

							if (im->UniqueName.size() > 0 && im->BaseName.size() > 0)
							{
								im->FullName = wstring(im->UniqueName + L" " + im->BaseName);
								wprintf(L"Full name: %s\n", im->FullName.c_str());
							}
							else if (im->UniqueName.size() == 0 && im->BaseName.size() > 0)
							{
								im->FullName = wstring(im->BaseName);
							}

							printf("Item Element/Sell ID: %d\n", im->InventoryEntityId);

							itms.push_back(im);

							if (g_Robot->DebugMode)
								printf("\tCell %d,%d: Child Element at: %llX (Entity %llX)\n", inventoryX, inventoryY, ChildChildElement, EntityAddr);
						}
					}
				}
			}
		}
	}				
			
	return itms;
}

std::list<Item*> StashInventory::GetInventoryItemsAtTab(int index)
{
	UINT64 poeBase = (UINT64)GetModuleHandleA(NULL);
	UINT64 ElementRoot = DereferenceSafe<UINT64>(poeBase + g_ProtectionServer->Offsets[8]);
	
	std::list<Item*> itms;

	if (ElementRoot == NULL)
		return itms;

	UINT64 ChildElement = DereferenceSafe<UINT64>(ElementRoot + Inventory::StashTab1Offset + (index * sizeof(UINT64)));

	if (ChildElement == NULL)
		return itms;


	UINT64 ChildElementList = DereferenceSafe<UINT64>(ChildElement + Offsets::Element::ChildsOffset);
	UINT64 ChildElementEnd = DereferenceSafe<UINT64>(ChildElement + Offsets::Element::ChildEndOffset);

	INT nElements = (ChildElementEnd - ChildElementList) / sizeof(UINT64);

	if (g_Robot->DebugMode)
		printf("nElements: %d, Inventory base: %llX, childList: %llX, end: %llX \n", nElements, ChildElement, ChildElementList, ChildElementEnd);

	for (int i = 1; i < nElements; i++) //first one has no entity, atleast for normalinv
	{
		UINT64 Child = DereferenceSafe<UINT64>(ChildElementList + (i * sizeof(UINT64)));

		if (Child != NULL) //
		{
			UINT64 EntityAddr = DereferenceSafe<UINT64>(Child + Inventory::EntityOffset);

			if (EntityAddr != NULL && (EntityAddr > 0x010000000000 && EntityAddr < 0x050000000000)) //incase some other stupid address is in the slot
			{
				int inventoryX = DereferenceSafe<int>(Child + Inventory::CellXOffset);
				int inventoryY = DereferenceSafe<int>(Child + Inventory::CellYOffset);

				int sizeX = DereferenceSafe<int>(Child + Inventory::CellWidthOffset);
				int sizeY = DereferenceSafe<int>(Child + Inventory::CellHeightOffset);

				if (sizeX > 0 && sizeY > 0)
				{
					Item* im = new Item();
					im->CellX = inventoryX;
					im->CellY = inventoryY;
					im->Height = sizeY;
					im->Width = sizeX;
					im->ItemEnt = new Entity(EntityAddr);
					
					im->StashPage = index;
					im->MemoryAddress = Child;
					im->InventoryEntityId = DereferenceSafe<UINT32>(Child + Inventory::EntityIdOffset);

					if (im->ItemEnt->GetComponentAddress("Base") != NULL)
					{
						wstring name = Base::GetBaseName(im->ItemEnt);

						if (name.size() > 0)
						{
							im->BaseName = wstring(name);
							wprintf(L"Base name: %s\n", name.c_str());
						}

						wstring price = Base::GetPublicPrice(im->ItemEnt);

						if (price.size() > 0)
						{
							im->PriceTag = wstring(price);
							wprintf(L"Price Tag: %s\n", price.c_str());
						}
					}
							

					if (im->ItemEnt->GetComponentAddress("Stack") != NULL)
					{
						im->stackSize = Stack::GetStackSize(im->ItemEnt);
						printf("Stack size: %d\n", im->stackSize);
					}

					if (im->ItemEnt->GetComponentAddress("Mods") > 0)
					{
						std::wstring namePtr = Mods::GetUniqueName(im->ItemEnt);
						wprintf(L"Item Unique Name: %s\n", namePtr.c_str());
						im->UniqueName = std::wstring(namePtr);
					}

					if (im->UniqueName.size() > 0 && im->BaseName.size() > 0)
					{
						im->FullName = wstring(im->UniqueName + L" " + im->BaseName);
						wprintf(L"Full name: %s\n", im->FullName.c_str());
					}
					else if (im->UniqueName.size() == 0 && im->BaseName.size() > 0)
					{
						im->FullName = wstring(im->BaseName);
					}

					itms.push_back(im);

					if (g_Robot->DebugMode)
						printf("\t Cell %d,%d: Child Element at: %llX (Entity %llX)\n", inventoryX, inventoryY, Child, EntityAddr);
				}
			}
		}
	}
		
	
	return itms;
}

std::list<Item*> TradeInventory::GetTradeWindowItems(int inventorySide, bool loadedStash) //this offsets changes based on whether youve interacted with stash...
{
	UINT64 poeBase = (UINT64)GetModuleHandleA(NULL);
	UINT64 ElementRoot = DereferenceSafe<UINT64>(poeBase + g_ProtectionServer->Offsets[8]);
	UINT64 ChildElement = 0;

	std::list<Item*> itms;

	if (ElementRoot == NULL)
		return itms;
	
	if (inventorySide == Inventory::Local && !loadedStash)
	{
		ChildElement = DereferenceSafe<UINT64>(ElementRoot + Inventory::TradeWindowOffset_OurItems); //doesnt work after loading stash!
	}
	else if (inventorySide == Inventory::Remote && !loadedStash)
	{
		ChildElement = DereferenceSafe<UINT64>(ElementRoot + Inventory::TradeWindowOffset_TheirItems);
	}
	else if (inventorySide == Inventory::Local && loadedStash)
	{
		ChildElement = DereferenceSafe<UINT64>(ElementRoot + Inventory::TradeWindowOffset_OurItems2); //same as stash page 1 offset.. very weird
	}
	else if (inventorySide == Inventory::Remote && loadedStash)
	{
		ChildElement = DereferenceSafe<UINT64>(ElementRoot + Inventory::TradeWindowOffset_TheirItems2);
	}

	if (!ChildElement)
		return itms;

	UINT64 ChildElementList = DereferenceSafe<UINT64>(ChildElement + Offsets::Element::ChildsOffset);
	UINT64 ChildElementEnd = DereferenceSafe<UINT64>(ChildElement + Offsets::Element::ChildEndOffset);

	INT nElements = (ChildElementEnd - ChildElementList) / sizeof(UINT64);

	if (g_Robot->DebugMode)
		printf("nElements: %d, Inventory base: %llX, childList: %llX, end: %llX \n", nElements, ChildElement, ChildElementList, ChildElementEnd);

	for (int i = 0; i < nElements; i++) // 1 item in trade window -> 3 child members, last one contains the entity?
	{
		UINT64 Child = DereferenceSafe<UINT64>(ChildElementList + (i * sizeof(UINT64)));

		if (Child != NULL)
		{
			UINT64 EntityAddr = DereferenceSafe<UINT64>(Child + Inventory::EntityOffset);

			if (EntityAddr != NULL && (EntityAddr > 0x010000000000 && EntityAddr < 0x050000000000)) //incase some other stupid address is in the slot
			{
				int inventoryX = DereferenceSafe<int>(Child + Inventory::CellXOffset);
				int inventoryY = DereferenceSafe<int>(Child + Inventory::CellYOffset);

				int sizeX = DereferenceSafe<int>(Child + Inventory::CellWidthOffset);
				int sizeY = DereferenceSafe<int>(Child + Inventory::CellHeightOffset);

				if (sizeX > 0 && sizeY > 0)
				{
					Item* im = new Item();
					im->CellX = inventoryX;
					im->CellY = inventoryY;
					im->Height = sizeY;
					im->Width = sizeX;
					im->ItemEnt = new Entity(EntityAddr);
					im->StashPage = NULL;
					im->MemoryAddress = Child;
					im->InventoryEntityId = DereferenceSafe<UINT32>(Child + Inventory::EntityIdOffset);

					if (im->ItemEnt->GetComponentAddress("Base") != NULL)
					{
						wstring name = Base::GetBaseName(im->ItemEnt);

						if (name.size() > 0)
						{
							im->BaseName = wstring(name);
							wprintf(L"Base name: %s\n", name.c_str());
						}
					}

					if (im->ItemEnt->GetComponentAddress("Mods") > 0)
					{
						std::wstring namePtr = Mods::GetUniqueName(im->ItemEnt);
						wprintf(L"Item Unique Name: %s\n", namePtr.c_str());
						im->UniqueName = std::wstring(namePtr);
					}


					if (im->ItemEnt->GetComponentAddress("Stack") != NULL)
					{
						im->stackSize = Stack::GetStackSize(im->ItemEnt);
						printf("Stack size: %d\n", im->stackSize);
					}

					if (im->UniqueName.size() > 0 && im->BaseName.size() > 0)
					{
						im->FullName = wstring(im->UniqueName + L" " + im->BaseName);
						wprintf(L"Full name: %s\n", im->FullName.c_str());
					}
					else if (im->UniqueName.size() == 0 && im->BaseName.size() > 0)
					{
						im->FullName = wstring(im->BaseName);
					}

					itms.push_back(im);

					if (g_Robot->DebugMode)
						printf("\t Cell %d,%d: Child Element at: %llX (Entity %llX)\n", inventoryX, inventoryY, Child, EntityAddr);
				}
			}
		}
	}
		


	return itms;

}

bool TradeInventory::ContainsItem(Inventory::TradeWindowSide side, wstring itemName, int quantity, bool isStashLoaded)
{
	std::list<Item*> items = GetTradeWindowItems(side, isStashLoaded);

	int totalQuantity = 0;

	if (items.size() > 0)
	{
		for each (Item* i in items)
		{
			if (iequals(i->FullName, itemName)) //might need to apply base name to full name
			{
				wprintf(L"Found item in trade window: %s (%d)\n", itemName.c_str(), quantity);
				totalQuantity += i->stackSize;
				
			}
			else if (iequals(i->BaseName, itemName))
			{
				wprintf(L"Found item in trade window: %s (%d)\n", itemName.c_str(), quantity);
				totalQuantity += i->stackSize;		
			}
		}
	}

	if (totalQuantity >= quantity)
		return true;
	else
		return false;
}


void StashInventory::ForceLoadTab(int index)
{
	PacketWriter* p = PacketBuilder::ChangeCurrentStashTab(index);
	UINT64 SendClass = GetSendClass();

	if (SendClass != NULL)
		SendPacket(SendClass, (LPBYTE)p->GetBuffer(), p->GetSize());

	delete p;
}

std::list<Item*> Inventory::GetFlasks(bool inventoryLoaded)
{
	std::list<Item*> flasks;
	UINT64 CurrentAddress = 0;

	UINT64 poeBase = (UINT64)GetModuleHandleA(NULL);
	UINT64 Ptr = DereferenceSafe<UINT64>(poeBase + g_ProtectionServer->Offsets[8]);

	if (Ptr == NULL)
		return flasks;
	
	if (!inventoryLoaded)
		CurrentAddress = DereferenceSafe<UINT64>(Ptr + 0xF8); //0xE8 -> flasks list	
	else	
		CurrentAddress = DereferenceSafe<UINT64>(Ptr + Inventory::FlaskInvOffset); //0xE8 -> flasks list
			
	if (CurrentAddress != NULL)
	{
		//we are now at the base inventory element.
		UINT64 ChildElementList = DereferenceSafe<UINT64>(CurrentAddress + Offsets::Element::ChildsOffset);
		UINT64 ChildElementEnd = DereferenceSafe<UINT64>(CurrentAddress + Offsets::Element::ChildEndOffset);

		INT nElements = (ChildElementEnd - ChildElementList) / sizeof(UINT64);

		if (g_Robot->DebugMode)
			printf("nElements: %d, Inventory base: %llX, childList: %llX, end: %llX \n", nElements, CurrentAddress, ChildElementList, ChildElementEnd);

		for (int i = 1; i < nElements; i++) //first one has no entity
		{
			UINT64 ChildElement = DereferenceSafe<UINT64>(ChildElementList + (i * sizeof(UINT64)));

			if (g_Robot->DebugMode)
				printf("ChildElement at: %llX\n", ChildElement);

			if (ChildElement != NULL) //
			{
				UINT64 EntityAddr = DereferenceSafe<UINT64>(ChildElement + Inventory::EntityOffset);

				if (EntityAddr != NULL && (EntityAddr > 0x010000000000 && EntityAddr < 0x050000000000))
				{
					int inventoryX = DereferenceSafe<int>(ChildElement + Inventory::CellXOffset);
					int inventoryY = DereferenceSafe<int>(ChildElement + Inventory::CellYOffset);

					int sizeX = DereferenceSafe<int>(ChildElement + Inventory::CellWidthOffset);
					int sizeY = DereferenceSafe<int>(ChildElement + Inventory::CellHeightOffset);

					if (sizeX > 0 && sizeY > 0)
					{
						Item* im = new Item();
						im->CellX = inventoryX;
						im->CellY = inventoryY;
						im->Height = sizeY;
						im->Width = sizeX;
						im->StashPage = 0;
						im->MemoryAddress = ChildElement;
						im->ItemEnt = new Entity(EntityAddr);
						im->InventoryEntityId = DereferenceSafe<UINT32>(ChildElement + Inventory::EntityIdOffset);

						if (im->ItemEnt->GetComponentAddress("Stack") > NULL)
						{
							im->stackSize = Stack::GetStackSize(im->ItemEnt);
							printf("Stack size: %d\n", im->stackSize);
						}
						else
						{
							im->stackSize = 1;
							printf("Stack size: %d\n", im->stackSize);
						}

						Inventory::FormInventoryItemName(im);

						flasks.push_back(im);

						if (g_Robot->DebugMode)
							printf("\tCell %d,%d: Child Element at: %llX (Entity %llX)\n", inventoryX, inventoryY, ChildElement, EntityAddr);
					}
				}
			}
		}
	}
	
	return flasks;
}

wstring Inventory::FormInventoryItemName(Item* itm)
{
	if (itm->ItemEnt->GetComponentAddress("Mods") > 0)
	{
		wstring namePtr = Mods::GetUniqueName(itm->ItemEnt);

		if (namePtr.size() > 0)
		{
			wprintf(L"Item Unique Name: %s\n", namePtr.c_str());
			itm->UniqueName = std::wstring(namePtr);
			itm->FullName = itm->UniqueName;
		}

	}

	if (itm->ItemEnt->GetComponentAddress("Base") != NULL)
	{
		wstring name = Base::GetBaseName(itm->ItemEnt);

		if (name.size() > 0)
		{
			itm->BaseName = wstring(name);
			wprintf(L"Base name: %s\n", name.c_str());

			if (itm->FullName.size() > 0)
				itm->FullName = itm->FullName + L" " + itm->BaseName;
			else
				itm->FullName = itm->BaseName;
		}
	}

	return itm->FullName;
}

wstring Inventory::FormItemName(GroundItem* itm)
{
	wstring fullName; 

	if (itm->GetComponentAddress("Mods") > 0)
	{
		wstring namePtr = Mods::GetUniqueName(itm);

		if (namePtr.size() > 0)
		{
			fullName = namePtr;
		}
	}

	if (itm->GetComponentAddress("Base") != NULL)
	{
		wstring name = Base::GetBaseName(itm);

		if (name.size() > 0)
		{
			if (fullName.size() > 0)
			{
				fullName = fullName + L" " + name;
			}
			else
				fullName = name;
		}
	}

	itm->FullName = fullName;
	return fullName;
}