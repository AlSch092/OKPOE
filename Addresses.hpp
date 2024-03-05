#pragma once
#include "Offsets.hpp"

struct MemoryLocations
{
	UINT64 Address;
	UINT64 Offset;
	CHAR* Name; //optional
};

MemoryLocations** FillAddresses(UINT64 PoEBase);

/******************
[0] = reveal map
[1] = Packet send
[2] = Log Entity
[3] = etc
******************/