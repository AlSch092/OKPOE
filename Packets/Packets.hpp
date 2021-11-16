#pragma once
#include "PacketBuilder.hpp"
#include <iostream>
#include <queue>
#include <random>
#include <string>

struct OutPacket
{
	byte padding_1[0xE8];
	UINT64 Unk1;
	byte padding_2[0x90];
	UINT64 LengthPrev; //0x180 -> moved into R8 then R8 moved into +188.
	UINT64 Length; //0x188
	byte padding_3[0x18];
	LPBYTE PtrBuffer;
};

namespace PacketHelper
{
	LPBYTE ToPacketFormat(CHAR* input);
	std::string* ToString(LPBYTE packetStr, int byteLength);
	int GetPacketLength(CHAR* input);
	void CreatePacket(LPBYTE data, UINT length);

	//typedef int(*SendOutbound)(UINT64 SendClass); 
};

std::string randomStr(size_t size);
std::wstring randomWStr(size_t size);
int32_t changeEndianness32(int32_t val);
UINT16 changeEndianness16(UINT16 val);