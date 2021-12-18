#include "Inventory.hpp"

extern AutoPlayer* Robot;
extern NetLogger* prot;

Inventory::Item* NormalInventory::GetInventoryItem(UINT64 ElementAddr)
{
	Inventory::Item* item = new Inventory::Item();
	
	if (item != NULL)
	{
		UINT64 CellX = DereferenceSafe<UINT64>(ElementAddr + Inventory::CellXOffset);
		UINT64 CellY = DereferenceSafe<UINT64>(ElementAddr + Inventory::CellYOffset);
		UINT64 EntityAddr = DereferenceSafe<UINT64>(ElementAddr + Inventory::EntityOffset);
		UINT64 Height = DereferenceSafe<UINT64>(ElementAddr + Inventory::CellHeightOffset);
		UINT64 Width = DereferenceSafe<UINT64>(ElementAddr + Inventory::CellWidthOffset);
		UINT64 IsHovered = DereferenceSafe<UINT64>(ElementAddr + Inventory::IsHoveredOffset);

		if (EntityAddr != NULL)
		{
			item->CellX = DereferenceSafe<UINT32>(CellX);
			item->CellY = DereferenceSafe<UINT32>(CellY);
			item->Height = DereferenceSafe<UINT32>(Height);
			item->Width = DereferenceSafe<UINT32>(Width);
			item->isHovered = DereferenceSafe<byte>(IsHovered);

			item->ItemEnt = new Entity(EntityAddr);
		}
	}

	return item;
}

std::list<Inventory::Item*> NormalInventory::GetInventoryItems()
{
	UINT64 poeBase = (UINT64)GetModuleHandleA(NULL);
	UINT64 Ptr = DereferenceSafe<UINT64>(poeBase + Offsets::PtrInventoryElement);
	std::list<Inventory::Item*> itms;

	if (Ptr != NULL)
	{
		UINT64 nextAddr = DereferenceSafe<UINT64>(Ptr + 0x78);

		if (nextAddr != NULL)
		{
			nextAddr = DereferenceSafe<UINT64>(nextAddr + 0x28);

			if (nextAddr != NULL)
			{
				//we are now at the base inventory element.
				UINT64 ChildElementList = DereferenceSafe<UINT64>(nextAddr + Element::ChildsOffset);
				UINT64 ChildElementEnd = DereferenceSafe<UINT64>(nextAddr + Element::ChildEndOffset);

				INT nElements = (ChildElementEnd - ChildElementList) / sizeof(UINT64);

				if (Robot->DebugMode)
					printf("nElements: %d, Inventory base: %llX, childList: %llX, end: %llX \n", nElements, nextAddr, ChildElementList, ChildElementEnd);	

				for (int i = 1; i < nElements; i++) //first one has no entity
				{
					UINT64 ChildElement = DereferenceSafe<UINT64>(ChildElementList + (i * sizeof(UINT64)));

					if (ChildElement != NULL) //
					{
						UINT64 EntityAddr = DereferenceSafe<UINT64>(ChildElement + Element::EntityOffset);

						if (EntityAddr != NULL && (EntityAddr > 0x010000000000 && EntityAddr < 0x030000000000))
						{
							int inventoryX = DereferenceSafe<int>(ChildElement + Element::CellXOffset);
							int inventoryY = DereferenceSafe<int>(ChildElement + Element::CellYOffset);

							int sizeX = DereferenceSafe<int>(ChildElement + Element::CellWidthOffset);
							int sizeY = DereferenceSafe<int>(ChildElement + Element::CellHeightOffset);

							if (sizeX > 0 && sizeY > 0)
							{
								Inventory::Item* im = new Inventory::Item();
								im->CellX = inventoryX;
								im->CellY = inventoryY;
								im->Height = sizeY;
								im->Width = sizeX;
								im->StashPage = 0;
								im->MemoryAddress = ChildElement;
								im->ItemEnt = new Entity(EntityAddr);
								im->ElementId = DereferenceSafe<UINT32>(ChildElement + Element::ElementIdOffset);

								if (im->ItemEnt->GetComponentAddress("Base") != NULL)
								{
									wstring name = Base::GetBaseName(im->ItemEnt);

									if (name.size() > 0)
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


								itms.push_back(im);

								if (Robot->DebugMode)
									printf("\tCell %d,%d: Child Element at: %llX (Entity %llX)\n", inventoryX, inventoryY, ChildElement, EntityAddr);
							}
						}
					}
				}
			}
		}
	}

	return itms;
}


std::list<Inventory::Item*> CurrencyInventory::GetInventoryItems()
{
	UINT64 poeBase = (UINT64)GetModuleHandleA(NULL);
	UINT64 Ptr = DereferenceSafe<UINT64>(poeBase + prot->Offsets[13]);
	std::list<Inventory::Item*> itms;

	if (Ptr != NULL)
	{
		UINT64 nextAddr = DereferenceSafe<UINT64>(Ptr + 0x4D0);

		if (nextAddr != NULL)
		{
			nextAddr = DereferenceSafe<UINT64>(nextAddr + 0x40);

			if (nextAddr != NULL)
			{
				nextAddr = DereferenceSafe<UINT64>(nextAddr + 0x08);
				nextAddr = DereferenceSafe<UINT64>(nextAddr + 0x50);
				
				//we are now at the base inventory element.
				UINT64 ChildElementList = DereferenceSafe<UINT64>(nextAddr + Element::ChildsOffset);
				UINT64 ChildElementEnd = DereferenceSafe<UINT64>(nextAddr + Element::ChildEndOffset);

				INT nElements = (ChildElementEnd - ChildElementList) / sizeof(UINT64);

				if (Robot->DebugMode)
					printf("nElements: %d, Inventory base: %llX, childList: %llX, end: %llX \n", nElements, nextAddr, ChildElementList, ChildElementEnd);

				if (nElements > 1)
				{
					for (int i = 0; i < nElements; i++)
					{
						UINT64 ChildElement = DereferenceSafe<UINT64>(ChildElementList + (i * sizeof(UINT64)));

						if (ChildElement != NULL) //
						{
							UINT64 subChildElementList = DereferenceSafe<UINT64>(ChildElement + Element::ChildsOffset);
							UINT64 subChildElementListEnd = DereferenceSafe<UINT64>(ChildElement + Element::ChildEndOffset);

							INT subElements = (subChildElementListEnd - subChildElementList) / sizeof(UINT64);

							if (subElements > 0 && subElements <= 2)
							{
								UINT64 ChildChildElement = DereferenceSafe<UINT64>(subChildElementList + sizeof(UINT64));

								if (ChildChildElement != NULL)
								{
									UINT64 EntityAddr = DereferenceSafe<UINT64>(ChildChildElement + Element::EntityOffset);

									if (EntityAddr != NULL && (EntityAddr > 0x010000000000 && EntityAddr < 0x040000000000))
									{
										int inventoryX = DereferenceSafe<int>(ChildChildElement + Element::CellXOffset);
										int inventoryY = DereferenceSafe<int>(ChildChildElement + Element::CellYOffset);

										int sizeX = DereferenceSafe<int>(ChildChildElement + Element::CellWidthOffset);
										int sizeY = DereferenceSafe<int>(ChildChildElement + Element::CellHeightOffset);

										if (sizeX > 0 && sizeY > 0)
										{
											Inventory::Item* im = new Inventory::Item();
											im->CellX = inventoryX;
											im->CellY = inventoryY;
											im->Height = sizeY;
											im->Width = sizeX;
											im->StashPage = 0;
											im->MemoryAddress = ChildChildElement;
											im->ItemEnt = new Entity(EntityAddr);
										
											im->ElementId = DereferenceSafe<UINT32>(ChildChildElement + Element::ElementIdOffset);

											if (im->ItemEnt->GetComponentAddress("Base") != NULL)
											{
												wstring name = Base::GetBaseName(im->ItemEnt);

												if (name.size() > 0)
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


											itms.push_back(im);

											if (Robot->DebugMode)
												printf("\tCell %d,%d: Child Element at: %llX (Entity %llX)\n", inventoryX, inventoryY, ChildChildElement, EntityAddr);
										}
									}
								}
							}
						}
					}				
				}
			}
		}
	}

	return itms;
}

std::list<Inventory::Item*> StashInventory::GetInventoryItemsAtTab(int index)
{
	UINT64 poeBase = (UINT64)GetModuleHandleA(NULL);
	UINT64 ElementRoot = DereferenceSafe<UINT64>(poeBase + prot->Offsets[13]);
	
	std::list<Inventory::Item*> itms;

	if (ElementRoot != NULL)
	{
		UINT64 ChildElement = DereferenceSafe<UINT64>(ElementRoot + Inventory::StashTab1Offset + (index * sizeof(UINT64)));

		if (ChildElement != NULL)
		{
			UINT64 ChildElementList = DereferenceSafe<UINT64>(ChildElement + Element::ChildsOffset);
			UINT64 ChildElementEnd = DereferenceSafe<UINT64>(ChildElement + Element::ChildEndOffset);

			INT nElements = (ChildElementEnd - ChildElementList) / sizeof(UINT64);

			if (Robot->DebugMode)
				printf("nElements: %d, Inventory base: %llX, childList: %llX, end: %llX \n", nElements, ChildElement, ChildElementList, ChildElementEnd);

			for (int i = 1; i < nElements; i++) //first one has no entity, atleast for normalinv
			{
				UINT64 Child = DereferenceSafe<UINT64>(ChildElementList + (i * sizeof(UINT64)));

				if (Child != NULL) //
				{
					UINT64 EntityAddr = DereferenceSafe<UINT64>(Child + Element::EntityOffset);

					if (EntityAddr != NULL && (EntityAddr > 0x010000000000 && EntityAddr < 0x050000000000)) //incase some other stupid address is in the slot
					{
						int inventoryX = DereferenceSafe<int>(Child + Element::CellXOffset);
						int inventoryY = DereferenceSafe<int>(Child + Element::CellYOffset);

						int sizeX = DereferenceSafe<int>(Child + Element::CellWidthOffset);
						int sizeY = DereferenceSafe<int>(Child + Element::CellHeightOffset);

						if (sizeX > 0 && sizeY > 0)
						{
							Inventory::Item* im = new Inventory::Item();
							im->CellX = inventoryX;
							im->CellY = inventoryY;
							im->Height = sizeY;
							im->Width = sizeX;
							im->ItemEnt = new Entity(EntityAddr);
					
							im->StashPage = index;
							im->MemoryAddress = Child;
							im->ElementId = DereferenceSafe<UINT32>(Child + Element::ElementIdOffset);

							if (im->ItemEnt->GetComponentAddress("Base") != NULL)
							{
								wstring name = Base::GetBaseName(im->ItemEnt);

								if (name.size() > 0)
								{
									im->BaseName = wstring(name);
									wprintf(L"Base name: %s\n", name.c_str());
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

							itms.push_back(im);

							if (Robot->DebugMode)
								printf("\t Cell %d,%d: Child Element at: %llX (Entity %llX)\n", inventoryX, inventoryY, Child, EntityAddr);
						}
					}
				}
			}
		}
	}

	return itms;

}

std::list<Inventory::Item*> TradeInventory::GetTradeWindowItems(int inventorySide)
{
	UINT64 poeBase = (UINT64)GetModuleHandleA(NULL);
	UINT64 ElementRoot = DereferenceSafe<UINT64>(poeBase + prot->Offsets[13]);
	UINT64 ChildElement = 0;

	std::list<Inventory::Item*> itms;

	if (ElementRoot != NULL)
	{
		if (inventorySide == Inventory::Local)
		{
			ChildElement = DereferenceSafe<UINT64>(ElementRoot + Inventory::TradeWindowOffset_OurItems);
		}
		else if (inventorySide == Inventory::Remote)
		{
			ChildElement = DereferenceSafe<UINT64>(ElementRoot + Inventory::TradeWindowOffset_TheirItems);
		}

		if (ChildElement != NULL)
		{
			UINT64 ChildElementList = DereferenceSafe<UINT64>(ChildElement + Element::ChildsOffset);
			UINT64 ChildElementEnd = DereferenceSafe<UINT64>(ChildElement + Element::ChildEndOffset);

			INT nElements = (ChildElementEnd - ChildElementList) / sizeof(UINT64);

			if (Robot->DebugMode)
				printf("nElements: %d, Inventory base: %llX, childList: %llX, end: %llX \n", nElements, ChildElement, ChildElementList, ChildElementEnd);

			for (int i = 0; i < nElements; i++) // 1 item in trade window -> 3 child members, last one contains the entity?
			{
				UINT64 Child = DereferenceSafe<UINT64>(ChildElementList + (i * sizeof(UINT64)));

				if (Child != NULL)
				{
					UINT64 EntityAddr = DereferenceSafe<UINT64>(Child + Element::EntityOffset);

					if (EntityAddr != NULL && (EntityAddr > 0x010000000000 && EntityAddr < 0x050000000000)) //incase some other stupid address is in the slot
					{
						int inventoryX = DereferenceSafe<int>(Child + Element::CellXOffset);
						int inventoryY = DereferenceSafe<int>(Child + Element::CellYOffset);

						int sizeX = DereferenceSafe<int>(Child + Element::CellWidthOffset);
						int sizeY = DereferenceSafe<int>(Child + Element::CellHeightOffset);

						if (sizeX > 0 && sizeY > 0)
						{
							Inventory::Item* im = new Inventory::Item();
							im->CellX = inventoryX;
							im->CellY = inventoryY;
							im->Height = sizeY;
							im->Width = sizeX;
							im->ItemEnt = new Entity(EntityAddr);
							im->StashPage = NULL;
							im->MemoryAddress = Child;
							im->ElementId = DereferenceSafe<UINT32>(Child + Element::ElementIdOffset);

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

							itms.push_back(im);

							if (Robot->DebugMode)
								printf("\t Cell %d,%d: Child Element at: %llX (Entity %llX)\n", inventoryX, inventoryY, Child, EntityAddr);
						}
					}
				}
			}
		}
	}

	return itms;

}

bool TradeInventory::ContainsItem(Inventory::TradeWindowSide side, wstring itemName, int quantity)
{
	std::list<Inventory::Item*> items = GetTradeWindowItems(side); //mabe replace this with @tab 5/6

	if (items.size() > 0)
	{
		for each (Inventory::Item* i in items)
		{
			if (wcscmp(i->ItemEnt->GetFilePathFromMemory().c_str(), itemName.c_str()) == 0)
			{
				wprintf(L"Found item in trade window: %s\n", itemName.c_str());
				return true;
			}
		}
	}

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
