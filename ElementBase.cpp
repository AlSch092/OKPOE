#include "ElementBase.hpp"

ElementBase::ElementBase(UINT64 MemoryAddress) : MemoryAddress(MemoryAddress)
{
	//fill in later
}

UINT32 ElementBase::GetElementId()
{
	return this->ElementId;
}

ElementBase* ElementBase::GetParent()
{
	return this->ParentElement;
}
std::list<ElementBase*> ElementBase::GetChildren()
{
	return this->ChildList;
}

std::wstring ElementBase::GetLabel()
{
	return this->swLabel;
}

void ElementBase::SetLabel(std::wstring label)
{
	this->swLabel = label;
}

wchar_t* ElementBase::GetLabelFromMemory(UINT64 _address)
{
	if (_address == NULL)
		return NULL;

	auto NextPtr = DereferenceSafe<UINT64>(_address + Offsets::Element::Label);
	auto labelCharCount = DereferenceSafe<UINT32>(_address + Offsets::Element::LabelCharacterCount);

	if (labelCharCount > 0 && labelCharCount < 45)
	{
		if (NextPtr)
		{
			UINT64 PtrLabel = NextPtr + Offsets::Element::Label_2;
			wchar_t* pLabel = reinterpret_cast<wchar_t*>(PtrLabel);

			if (wcslen(pLabel) == labelCharCount)
			{
				this->swLabel = std::wstring(pLabel);
				return pLabel;
			}
			else
			{
				UINT64 PtrLabel = DereferenceSafe<UINT64>(NextPtr + Offsets::Element::Label_2);
				wchar_t* pLabel = reinterpret_cast<wchar_t*>(PtrLabel);

				if (wcslen(pLabel) == labelCharCount)
				{
					this->swLabel = std::wstring(pLabel);
					return pLabel;
				}
			}
		}
		else
			return NULL;		
	}

	return NULL;
}