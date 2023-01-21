#pragma once
#include "PacketBuilder.hpp"
#include <iostream>
#include <queue>
#include <random>
#include <string>

namespace PacketHelper
{
	std::string randomStr(size_t size);
	std::wstring randomWStr(size_t size);

	uint16_t changeEndianness16(UINT16 val);
	int32_t changeEndianness32(int32_t val);

	LPBYTE ToPacketFormat(CHAR* input);
	std::string ToString(LPBYTE packetStr, int byteLength);

	int GetPacketLength(CHAR* input);

	void CreatePacket(LPBYTE data, UINT length);

	void SendPacket(UINT64 SendClass, LPBYTE Data, UINT64 Length);
};
