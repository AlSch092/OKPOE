#pragma once
#include <Windows.h>
#include <string>

typedef struct 
{

	UINT64 dwJunk1;

	UINT64 IndexPtr;
	UINT32 Index;

	UINT64 NamePtrAddress;
	std::string Name;

	UINT64 ComponentAddress;
}ComponentListNode;