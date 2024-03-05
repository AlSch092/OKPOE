#include "Base.hpp"

std::wstring Base::GetBaseName(Entity* e)
{
	UINT64 BaseCompAddr = e->GetComponentAddress("Base");
	std::wstring baseName;

	if (BaseCompAddr == NULL)
	{
		printf("[ERROR] BaseName was NULL.\n");
		return baseName;
	}

	UINT64 InternalPtr = DereferenceSafe<UINT64>(BaseCompAddr + Base::Offsets::FurtherDetailsPtr);

	if (InternalPtr != NULL) //sometimes its the string at the address, sometimes its a pointer to a string..
	{
		UINT64 NamePtrAddr = *(UINT64*)(InternalPtr + Base::Offsets::BaseName); //sometimes a ptr, not always. . .
		
		if (DereferenceSafe<UINT64>(NamePtrAddr) != NULL)
		{
			__try
			{			
				baseName = std::wstring((const wchar_t*)NamePtrAddr); //crash. . .		
			}
			__except (EXCEPTION_EXECUTE_HANDLER)
			{
				baseName = L"";
			}
		}
	}

	return baseName;
}

bool Base::IsElder(Entity* e)
{
	UINT64 BaseCompAddr = e->GetComponentAddress("Base");

	if (BaseCompAddr == NULL)
		return 0;	

	bool isElder = DereferenceSafe<bool>(BaseCompAddr + Base::Offsets::IsElder);

	return isElder;
}

bool Base::IsShaper(Entity* e)
{
	UINT64 BaseCompAddr = e->GetComponentAddress("Base");

	if (BaseCompAddr == NULL)
		return 0;

	bool isShaper = DereferenceSafe<bool>(BaseCompAddr + Base::Offsets::IsShaper);

	return isShaper;
}

bool Base::IsCorrupted(Entity* e)
{
	UINT64 BaseCompAddr = e->GetComponentAddress("Base");

	if (BaseCompAddr == NULL)
		return 0;

	bool corrupted = DereferenceSafe<bool>(BaseCompAddr + Base::Offsets::IsCorrupted);

	return corrupted;
}

std::wstring Base::GetPublicPrice(Entity* e)
{
	UINT64 BaseCompAddr = e->GetComponentAddress("Base");
	
	if (BaseCompAddr == NULL)
		return L"";

	UINT64 PriceAddr = DereferenceSafe<UINT64>(BaseCompAddr + Base::Offsets::PublicPrice);

	if (PriceAddr != NULL)
	{
		printf("Price Address: %llX\n", PriceAddr);
		wchar_t* tagPtr = (wchar_t*)PriceAddr;
		return std::wstring(tagPtr);
	}

	return L"";
}