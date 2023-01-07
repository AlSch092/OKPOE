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

Entity* ElementBase::GetEntity()
{
	return this->_Entity;
}

std::wstring ElementBase::GetLabel() //see Element::GetLabel for reading in-game labels
{
	return this->swLabel;
}
