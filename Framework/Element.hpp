#pragma once
#include "ElementBase.hpp"

namespace Element  //unmanaged code of elements, being replaced by ElementBase class (ElementBase.hpp)
{
	void PrintHoveredElements(); 
	
	UINT64 GetChildElement(UINT64 StartingElement);
	UINT64 GetChildElementAtIndex(UINT64 Element, int index);
	unsigned int GetElementId(UINT64 ElementAddr);
	Entity* GetEntityAt(UINT64 ElementBase);

	std::list<ElementBase*> GetScreenElements();

	wchar_t* GetLabel(UINT64 ElementAddress);
	bool HasLabel(UINT64 ElementAddress, std::wstring label);
	bool IsLabelOnScreen(std::wstring label);
};
