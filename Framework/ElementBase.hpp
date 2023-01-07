#pragma once
#include "Entity.hpp"

class ElementBase
{
public:

	ElementBase() {};
	ElementBase(UINT64 _Addr); //initialize all members from constructor

	ElementBase* GetParent(); 
	std::list<ElementBase*> GetChildren();

	Entity* GetEntity();

	std::wstring GetLabel();

	UINT32 GetElementId();

	bool isVisible();

private:
	int ElementId;
	UINT64 MemoryAddress;
	std::wstring swLabel;

	ElementBase* ParentElement;
	std::list<ElementBase*> ChildList;

	bool bVisible;

	Entity* _Entity;

};
