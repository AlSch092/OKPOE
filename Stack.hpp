#pragma once
#include "Entity.hpp"

namespace Stack
{
	static UINT64 InternalPtrOffset = 0x10;
	static UINT64 CurrentCountOffset = 0x18;

	static UINT64 InternalPtr_MaxSizeOffset = 0x28;

	struct InternalPtr
	{
		int MaxStackSizeInCurrencyStashTab;
		int MaxStackSize;
	};

	int GetStackSize(Entity* e);
}