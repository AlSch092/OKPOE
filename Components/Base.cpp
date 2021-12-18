#include "Base.hpp"

std::wstring Base::GetBaseName(Entity* e)
{
	UINT64 BaseCompAddr = e->GetComponentAddress("Base");
	std::wstring baseName;

	if (BaseCompAddr == NULL)
	{
		return 0;
	}

	UINT64 InternalPtr = DereferenceSafe<UINT64>(BaseCompAddr + Base::InternalPtrOffset);
	
	if (InternalPtr != NULL)
	{
		UINT64 NamePtrAddr = (UINT64)(InternalPtr + Base::BaseNameOffset); //sometimes a ptr, not always. . .
		wchar_t* NamePtr = (wchar_t*)NamePtrAddr;
	
		if (NamePtr[0] >= L'A' &&  NamePtr[0] <= L'Z')
		{
			baseName = std::wstring((const wchar_t*)NamePtrAddr);
		}
		else
		{
			NamePtrAddr = DereferenceSafe<UINT64>(NamePtrAddr);

			if (NamePtrAddr != NULL)
			{
				baseName = std::wstring((const wchar_t*)NamePtrAddr);
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

	bool isElder = DereferenceSafe<bool>(BaseCompAddr + Base::IsElderOffset);

	return isElder;
}

bool Base::IsShaper(Entity* e)
{
	UINT64 BaseCompAddr = e->GetComponentAddress("Base");

	if (BaseCompAddr == NULL)
		return 0;

	bool isShaper = DereferenceSafe<bool>(BaseCompAddr + Base::IsShaperOffset);

	return isShaper;
}

bool Base::IsCorrupted(Entity* e)
{
	UINT64 BaseCompAddr = e->GetComponentAddress("Base");

	if (BaseCompAddr == NULL)
		return 0;

	bool corrupted = DereferenceSafe<bool>(BaseCompAddr + Base::IsCorruptedOffset);

	return corrupted;
}
