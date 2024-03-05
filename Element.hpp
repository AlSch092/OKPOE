#pragma once
#include "ElementBase.hpp"

namespace Element  //unmanaged code of elements, being replaced by ElementBase class (ElementBase.hpp)
{
	struct Node {
		int value;
		int num_children;
		struct Node** children;
	};

	void PrintHoveredElements(); 
	
	UINT64 GetChildElement(UINT64 StartingElement);
	UINT64 GetChildElementAtIndex(UINT64 Element, int index);
	unsigned int GetElementId(UINT64 ElementAddr);
	Entity* GetEntityAt(UINT64 ElementBase);

	std::list<ElementBase*> GetScreenElements();

	wchar_t* GetLabel(UINT64 ElementAddress);
	bool HasLabel(UINT64 ElementAddress, std::wstring label);
	bool IsSubstringLabelOnScreen(std::wstring label);
	bool IsLabelOnScreen(std::wstring label);


};

namespace ElementIds
{
	//const uint32_t Stash = 0x698; //likely not right
	//const uint32_t TrialStingingDoubt = 0x238;
}