#pragma once
#include <Windows.h>
#include <string>

struct ComponentListNode //doubly link list
{
	UINT64 NextPtr;
	UINT64 PrevPtr;

	UINT64 IndexPtr;
	UINT32 Index;

	UINT64 NamePtrAddress;
	char Name[50];
};

struct NewComponentListNode
{
	UINT64 dwJunk1;

	UINT64 IndexPtr;
	UINT32 Index;

	UINT64 NamePtrAddress;
	char Name[50];
};