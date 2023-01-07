#include "Element.hpp"
#include "NetLogger.hpp"
#include "Inventory.hpp"

extern NetLogger* prot;

//being replaced with ElementBase class!

bool Element::IsLabelOnScreen(std::wstring label)
{
	auto allElements = GetScreenElements();

	for each (ElementBase* eb in allElements)
	{
		if (eb->GetLabel().c_str() != NULL)
		{
			if (eb->GetLabel() == label)
			{
				wprintf(L"Found label on screen! %s\n", eb->GetLabel());
				return true;
			}
		}
	}

	return false;
}

bool Element::HasLabel(UINT64 ElementAddress, std::wstring wsLabel)
{
	if (ElementAddress == NULL)
		return false;

	std::wstring label = GetLabel(ElementAddress);

	if (wsLabel == label)
		return true;
	else
		return false;
}

wchar_t* Element::GetLabel(UINT64 ElementAddress)
{
	if (ElementAddress == NULL)
		return NULL;

	auto NextPtr = DereferenceSafe<UINT64>(ElementAddress + Offsets::Element::Label);
	auto labelCharCount = DereferenceSafe<UINT32>(ElementAddress + Offsets::Element::LabelCharacterCount);

	if (labelCharCount > 0 && labelCharCount < 45)
	{
		if (NextPtr)
		{
			UINT64 PtrLabel = NextPtr + Offsets::Element::Label_2;
			wchar_t* pLabel = reinterpret_cast<wchar_t*>(PtrLabel);

			if (wcslen(pLabel) == labelCharCount)
			{			
				return pLabel;		
			}
			else
			{
				UINT64 PtrLabel = DereferenceSafe<UINT64>(NextPtr + Offsets::Element::Label_2);
				wchar_t* pLabel = reinterpret_cast<wchar_t*>(PtrLabel);
				
				if (wcslen(pLabel) == labelCharCount)
				{		
					return pLabel;
				}
			}
		}
		else
		{
			return NULL;
		}
	}

	return NULL;
}

void Element::PrintHoveredElements()
{
	UINT64 HoverElementAddr = 0;
	UINT64 poeBase = (UINT64)GetModuleHandleA(NULL);

	while (true)
	{
		UINT64 StatePtr = DereferenceSafe<UINT64>(poeBase + prot->Offsets[1]);

		if (StatePtr != NULL)
		{
			UINT64 copyHoverElement = HoverElementAddr;
			HoverElementAddr = DereferenceSafe<UINT64>(StatePtr + Offsets::IngameState::UIHoveredElement);

			if (HoverElementAddr != NULL && HoverElementAddr != copyHoverElement) //mouse is over some element, use copy to prevent spamming
			{
				UINT64 ChildListAddr = DereferenceSafe<UINT64>(HoverElementAddr + Offsets::Element::ChildsOffset);
				UINT64 ChildListEndingAddr = DereferenceSafe<UINT64>(HoverElementAddr + Offsets::Element::ChildEndOffset);
				
				int nElements = (ChildListEndingAddr - ChildListAddr) / sizeof(UINT64);

				if (nElements == 1 || nElements == 2) //2 is an item with sockets, 1 is a nonsockets item
				{
					UINT64 EntityAddr = DereferenceSafe<UINT64>(HoverElementAddr + Inventory::EntityOffset);

					if (EntityAddr != NULL) //very sloppy code, needs more functions added for Item* struct, etc.
					{		
						int inventoryX = DereferenceSafe<int>(HoverElementAddr + Inventory::CellXOffset);
						int inventoryY = DereferenceSafe<int>(HoverElementAddr + Inventory::CellYOffset);

						int sizeX = DereferenceSafe<int>(HoverElementAddr + Inventory::CellWidthOffset);
						int sizeY = DereferenceSafe<int>(HoverElementAddr + Inventory::CellHeightOffset);

						Item* im = new Item();
						im->CellX = inventoryX;
						im->CellY = inventoryY;
						im->Height = sizeY;
						im->Width = sizeX;
						im->StashPage = 0;
						im->MemoryAddress = HoverElementAddr;
						im->ItemEnt = new Entity(EntityAddr);
						im->InventoryEntityId = DereferenceSafe<UINT32>(HoverElementAddr + Inventory::EntityIdOffset);

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

						wprintf(L"Item Name: %s\n", im->FullName.c_str());
						wprintf(L"X,Y: %d, %d \n", im->CellX, im->CellY);

					}
				}
			}
		}
		else
		{
			Sleep(2000);
		}

		Sleep(1000);
	}

}

std::list<ElementBase*> Element::GetScreenElements() //working: gets all elements on screen (ex Label found: Dannig, Warrior Skald, Label found: Tane Octavius, Label found: Niko, Master of the Depths)
{
	auto poeBase = (UINT64)GetModuleHandleA(NULL);
	auto StatePtr = DereferenceSafe<UINT64>(poeBase + prot->Offsets[1]);
	
	std::list<ElementBase*> gameElements;

	auto RootElement = 0, ChildElementList = 0;

	if (StatePtr != NULL)
	{
		UINT64 UIRoot = StatePtr + Offsets::IngameState::IngameUI;
		UIRoot = DereferenceSafe<UINT64>(UIRoot);

		auto RootElement = new ElementBase(UIRoot);
		gameElements.push_back(RootElement);

		if (UIRoot != NULL)
		{
			auto RootElement = UIRoot;

			if (RootElement != NULL)
			{
				auto ChildElementList = DereferenceSafe<UINT64>(RootElement + Offsets::Element::ChildsOffset);
				auto ChildElementEnd = DereferenceSafe<UINT64>(RootElement + Offsets::Element::ChildEndOffset);
				
				UINT nElements = (ChildElementEnd - ChildElementList) / sizeof(UINT64);
				
				if (nElements > 100)
				{
					if (nElements > 10) //screen seems to be the 7th in the list? not always....
					{
						auto labelsElement = DereferenceSafe<UINT64>(ChildElementList + 0x30); //7th

						auto FinalChildElementList = DereferenceSafe<UINT64>(labelsElement + Offsets::Element::ChildsOffset);
						auto FinalChildElementEnd = DereferenceSafe<UINT64>(labelsElement + Offsets::Element::ChildEndOffset);

						auto nElements = (FinalChildElementEnd - FinalChildElementList) / sizeof(UINT64);

						auto labelsElement2 = DereferenceSafe<UINT64>(FinalChildElementList);

						FinalChildElementList = DereferenceSafe<UINT64>(labelsElement2 + Offsets::Element::ChildsOffset);
						FinalChildElementEnd = DereferenceSafe<UINT64>(labelsElement2 + Offsets::Element::ChildEndOffset);

						nElements = (FinalChildElementEnd - FinalChildElementList) / sizeof(UINT64);

						for (int i = 0; i < nElements; i++)
						{
							auto ChildElement = DereferenceSafe<UINT64>(FinalChildElementList + (i * sizeof(UINT64)));

							auto _element = new ElementBase(ChildElement);
							
							auto label = GetLabel(ChildElement);

							if (label != NULL)
							{
								if (wcslen(label) > 0) //finally, we found the label. add it to the element
								{
									_element->GetLabel() = std::wstring(label);
								}
							}
			
							gameElements.push_back(_element);

							int j = 0;
						}

					}
				}
			}
		}
	}
	else
	{
		printf("IngameState Ptr::UI was NULL.\n");
	}

	return gameElements;
}

//base/noElement contains 2 parents to inventory 
UINT64 Element::GetChildElement(UINT64 StartingElement)
{
	if (StartingElement != NULL)
	{
		UINT64 ChildElementList = DereferenceSafe<UINT64>(StartingElement + Offsets::Element::ChildsOffset);
		UINT64 ChildElementEnd = DereferenceSafe<UINT64>(StartingElement + Offsets::Element::ChildEndOffset);

		UINT nElements = (ChildElementEnd - ChildElementList) / sizeof(UINT64);

		if (ChildElementList == ChildElementEnd)
			nElements = 0;

		printf("nElements: %d\n", nElements);
		printf("ChildElementList: %llX\n", ChildElementList);
		printf("ChildElementEnd: %llX\n", ChildElementEnd);

		for (int i = 0; i < nElements; i++)
		{
			UINT64 ChildElement = DereferenceSafe<UINT64>(ChildElementList + (i * sizeof(UINT64)));

			while (ChildElement != NULL && (ChildElement > 0x10000000000 && ChildElement < 0x30000000000))
			{
				UINT64 EntityAddr = DereferenceSafe<FLOAT>(ChildElement + Inventory::EntityOffset);

				if (EntityAddr != NULL)
				{
					Entity* e = new Entity(EntityAddr);
					printf("\tChild Element at: %llX (Entity %llX)\n", ChildElement, EntityAddr);
						
				}
				else
				{
					printf("\tChild Element at: %llX \n", ChildElement);
				}

				ChildElement = GetChildElement(ChildElement);
			}
		}
	}

	return NULL;
}

UINT64 Element::GetChildElementAtIndex(UINT64 Element, int index)
{
	if (Element == NULL)
		return 0;

	UINT64 ChildElementList = DereferenceSafe<UINT64>(Element + Offsets::Element::ChildsOffset);
	UINT64 ChildElementEnd = DereferenceSafe<UINT64>(Element + Offsets::Element::ChildEndOffset);

	UINT nElements = (ChildElementEnd - ChildElementList) / sizeof(UINT64);

	if (index > nElements)
		return 0;

	return DereferenceSafe<UINT64>(ChildElementList + (index * sizeof(UINT64)));
}

unsigned int Element::GetElementId(UINT64 ElementAddr)
{
	if (ElementAddr == NULL)
		return 0;

	return DereferenceSafe<unsigned int>(ElementAddr + Inventory::EntityIdOffset);
}

Entity* Element::GetEntityAt(UINT64 ElementBase)
{
	//read offset of entity ptr in element and return new entity class, will finish soon
	return NULL;
}
