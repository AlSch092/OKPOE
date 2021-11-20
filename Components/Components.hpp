#pragma once
#include <Windows.h>
#include <string>

struct ComponentListNode //doubly link list - pre 3.16
{
	UINT64 NextPtr;
	UINT64 PrevPtr;

	UINT64 IndexPtr;
	UINT32 Index;

	UINT64 NamePtrAddress;
	char Name[50];
};

struct NewComponentListNode //as of 3.16 we no longer are given a doublelink list, but instead some gross blob of non-contiguous memory at +0x30, +0x30 of entity.
{
	UINT64 IndexPtr;
	UINT32 Index;

	UINT64 NamePtrAddress;
	char Name[50];
};
