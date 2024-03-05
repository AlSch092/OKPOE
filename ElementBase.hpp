#pragma once
#include "Entity.hpp"

class ElementBase
{
public:

	ElementBase() {};
	ElementBase(UINT64 _Addr); //initialize all members from constructor

	ElementBase* GetParent(); 
	std::list<ElementBase*> GetChildren();

	std::wstring GetLabel(); //not all elements will have this, thus we should put this into some inherited class for labelElements. for now we leave here.
	wchar_t* GetLabelFromMemory(UINT64 _address);

	UINT32 GetElementId();

	bool isVisible();

	void SetLabel(std::wstring label);

private:
	int ElementId;
	UINT64 MemoryAddress;
	std::wstring swLabel;

	ElementBase* ParentElement;
	std::list<ElementBase*> ChildList;

	bool bVisible;

	Entity* _Entity;

};