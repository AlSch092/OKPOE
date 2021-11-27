#include "Element.hpp"
#include "FileIO.hpp"

void Element::GetAllElements()
{
	UINT64 poeBase = (UINT64)GetModuleHandleA(NULL);
	UINT64 StatePtr = DereferenceSafe<UINT64>(poeBase + Offsets::IngameState);
	UINT64 HoverElementAddr = 0;
	UINT64 RootElement = 0;
	UINT64 ChildElementList = 0;

	if (StatePtr != NULL)
	{
		UINT64 UIRoot = StatePtr + Offsets::IngameState::IngameUI;
    
		if (UIRoot != NULL)
		{
			UINT64 RootElement = DereferenceSafe<UINT64>(UIRoot);

			if (RootElement != NULL)
			{
				UINT64 ChildElementList = DereferenceSafe<UINT64>(RootElement + Element::ChildsOffset);
				UINT64 ChildElementEnd = DereferenceSafe<UINT64>(RootElement + Element::ChildEndOffset);
				
				UINT nElements = (ChildElementEnd - ChildElementList) / sizeof(uint64_t);
		
				printf("nElements: %d\n", nElements);
				printf("ChildElementList: %llX\n", ChildElementList);
				printf("ChildElementEnd: %llX\n", ChildElementEnd);

				for (int i = 0; i < nElements; i++)
				{
					UINT64 ChildElement = DereferenceSafe<UINT64>(ChildElementList + (i * sizeof(uint64_t)));

					int j = 0;

					while (ChildElement != NULL)
					{
						UINT64 EntityAddr = DereferenceSafe<FLOAT>(ChildElement + Element::EntityOffset);
						
						if (EntityAddr != NULL)
						{
							printf("\tChild Element %d at: %llX (Entity %llX)\n", j, ChildElement, EntityAddr);

							//Entity* e = new Entity(EntityAddr);
							//e->FillComponentList();

							//wstring path = e->GetFilePathFromMemory();
							//wprintf(L"Entity Path: %s\n", path.c_str());
						}
						else
						{
							printf("\tChild Element at: %llX \n", ChildElement);
						}
			
						ChildElement = GetChildElement(ChildElement);
						j++;
					}
				}
			}
		}
	}
	else
	{
		FileIO::Log("IngameState Ptr::UI was NULL.\n");
		return;
	}
}

//base/noElement contains 2 parents to inventory .. call this recursively to get all elements from root
UINT64 Element::GetChildElement(UINT64 StartingElement)
{
	if (StartingElement != NULL)
	{
		UINT64 ChildElementList = DereferenceSafe<UINT64>(StartingElement + Element::ChildsOffset);
		UINT64 ChildElementEnd = DereferenceSafe<UINT64>(StartingElement + Element::ChildEndOffset);

		UINT nElements = (ChildElementEnd - ChildElementList) / sizeof(uint64_t);

		printf("nElements: %d\n", nElements);
		printf("ChildElementList: %llX\n", ChildElementList);
		printf("ChildElementEnd: %llX\n", ChildElementEnd);

		for (int i = 0; i < nElements; i++)
		{
			UINT64 ChildElement = DereferenceSafe<UINT64>(ChildElementList + (i * sizeof(uint64_t)));

			if (ChildElement != NULL)
			{
				UINT64 EntityAddr = DereferenceSafe<FLOAT>(ChildElement + Element::EntityOffset);

				if (EntityAddr != NULL)
				{
					printf("\tChild Element at: %llX (Entity %llX)\n", ChildElement, EntityAddr);

					//Entity* e = new Entity(EntityAddr);
					//e->FillComponentList();

					//wprintf(L"\tEntity Path: %s\n", e->GetFilePathFromMemory().c_str());
				}
				else
				{
					printf("\tChild Element at: %llX \n", ChildElement);
				}

				return ChildElement;
			}
			else
			{
				return NULL;
			}
		}
	}

	return NULL;
}
