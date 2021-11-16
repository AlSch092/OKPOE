#pragma once
#include "Entity.hpp"

namespace MinimapIcon
{
	static const UINT64 IconInternalPtr = 0x20;
	static const UINT64 IsHidden = 0x34;

	void MapIconsHook(UINT64 IconStructAddr);
}

namespace MinimapIconInternal
{
	static const UINT64 IconNamePtr = 0x00; //
	static const UINT64 IconRadius = 0x08; //
	static const UINT64 LargeIconRadius = 0x0C; //
	static const UINT64 Unk1 = 0x10; //
	static const UINT64 Unk2 = 0x11;
	static const UINT64 Unk3 = 0x12;
	static const UINT64 IconPointerMaxDistance = 0x13;
}