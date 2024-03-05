#pragma once
#include "PacketBuilder.hpp"
#include <iostream>
#include <queue>
#include <random>
#include <string>

namespace PacketHelper //for GUI/formatting of packets
{
	std::string randomStr(size_t size);
	std::wstring randomWStr(size_t size);

	uint16_t changeEndianness16(uint16_t val);
	uint32_t changeEndianness32(uint32_t val);
	uint64_t changeEndianness64(uint64_t val);

	LPBYTE ToPacketFormat(const CHAR* __in input);
	std::string ToString(LPBYTE packetStr, int byteLength);

	std::string string_to_hex(const std::string& input);
	std::string hex_to_string(const std::string& input);

	int GetPacketLength(const CHAR* __in input);

	void CreatePacket(LPBYTE data, UINT length);

	void Send(UINT64 SendClass, LPBYTE Data, UINT64 Length);
};
