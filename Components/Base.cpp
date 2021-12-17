#include "Base.hpp"

std::wstring Base::GetBaseName(Entity* e)
{
	UINT64 BaseCompAddr = e->GetComponentAddress("Base");

	if (BaseCompAddr == NULL)
	{
		return 0;
	}

	UINT64 InternalPtr = DereferenceSafe<UINT64>(BaseCompAddr + Base::InternalPtrOffset);

	if (InternalPtr != NULL)
	{
		UINT64 NamePtrAddr = DereferenceSafe<UINT64>(InternalPtr + Base::BaseNameOffset);
		wchar_t* namePtr = (wchar_t*)NamePtrAddr;
		return std::wstring(namePtr);
	}

	return 0;
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
