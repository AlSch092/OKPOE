#include "NetLogger.hpp"
#define OFFSET_SUM 0xB3902E8

NetLogger::NetLogger()
{
	//printf("BoE Debug: NetLogger Enabled \n");

	this->CryptoKey = new std::vector<char>();

	for (int i = 0; i < 8; i++)
	{
		char j = i;
		this->CryptoKey->push_back(j);
	}

	this->IsCompromised = FALSE;
}

BOOL NetLogger::SetSocket(SOCKET S)
{
	if (S != NULL)
	{
		this->Socket = S;
		return TRUE;
	}

	this->Socket = NULL;
	return FALSE;
}

BOOL NetLogger::SetSocketPort(USHORT Port)
{
	if (Port != 0)
	{
		this->Port = Port;
		return TRUE;
	}

	this->Port = 0;
	return FALSE;
}

BOOL NetLogger::SetIP(const char* IP)
{
	return TRUE;
}

BOOL NetLogger::GetClientIPv4(IPv4 & myIP)
{
	char szBuffer[1024];

#ifdef WIN32
	WSADATA wsaData;
	WORD wVersionRequested = MAKEWORD(2, 0);
	if (::WSAStartup(wVersionRequested, &wsaData) != 0)
		return false;
#endif


	if (gethostname(szBuffer, sizeof(szBuffer)) == SOCKET_ERROR)
	{
#ifdef WIN32
		WSACleanup();
#endif
		return false;
	}

	struct hostent *host = gethostbyname(szBuffer);
	if (host == NULL)
	{
#ifdef WIN32
		WSACleanup();
#endif
		return false;
	}

	//Obtain the computer's IP
	myIP.b1 = ((struct in_addr *)(host->h_addr))->S_un.S_un_b.s_b1;
	myIP.b2 = ((struct in_addr *)(host->h_addr))->S_un.S_un_b.s_b2;
	myIP.b3 = ((struct in_addr *)(host->h_addr))->S_un.S_un_b.s_b3;
	myIP.b4 = ((struct in_addr *)(host->h_addr))->S_un.S_un_b.s_b4;

#ifdef WIN32
	WSACleanup();
#endif
	return true;
}

ItemEntry* NetLogger::GetItemEntries(LPWSTR PathName)
{
	return new ItemEntry();
}

bool NetLogger::SendHWID()
{
	WSADATA wsaData;
	SOCKET Socket = INVALID_SOCKET;
	SOCKADDR_IN SockAddr;
	
	std::string HWID = this->FillHardwareID();

	unsigned char buffer[512] = { 0 };
	
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		//printf("WSAStartup failed: %d.\n", WSAGetLastError());
		return false;
	}

	//for (int i = 0; i < strlen(url); i++) //unmask the URL by xorring..
	//{
	//	url[i] = url[i] ^ NetCipher::XorKey;
	//}

	Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	SockAddr.sin_addr.S_un.S_addr = inet_addr(GetUnpackedServerIP().c_str());
	SockAddr.sin_port = htons(5445);
	SockAddr.sin_family = AF_INET;

	this->Socket = Socket;

	if (connect(Socket, (SOCKADDR*)(&SockAddr), sizeof(SockAddr)) != 0)
	{
		this->HelloApproved = false;
		return false;
	}

	byte* CipherHWID = NetCipher::CipherString((char*)HWID.c_str());
	int CipherLen = strlen(HWID.c_str());

	int BytesSent = send(Socket, (const char*)CipherHWID, CipherLen, 0);

	int nDataLength;

	if (BytesSent >= strlen(HWID.c_str())) //make sure we sent the hwid
	{
		while ((nDataLength = recv(Socket, (char*)buffer, 512, 0)) == 0); 

		if (nDataLength > 8 * 5) //change this later... MINIMUM OFFSETS NEEDED..
		{
			int nOffsets = nDataLength / 8;

			UINT64 Sum = 0;

			for (int i = 0; i < nOffsets; i++)
			{
				memcpy((void*)&Offsets[i], (void*)&buffer[i * 8], 8);
				Sum = Sum + Offsets[i];
			}

			if (Sum > 0xE000000)
			{
				this->HelloApproved = true;

				//create listener thread
				//HANDLE ListenerThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&NetLogger::Listen, this, 0, 0);
				//return this->HelloApproved;
			}
		}


	}

	//closesocket(Socket);
	//WSACleanup();
	//shutdown(Socket, 0);

	return this->HelloApproved;
}

void NetLogger::Listen(LPVOID param)
{
	NetLogger* p = reinterpret_cast<NetLogger*>(param);
	char buffer[512];

	bool recieving = true;

	while (recieving)
	{
		int nDataLength = recv(p->Socket, (char*)buffer, 512, 0);

		if (nDataLength != SOCKET_ERROR && nDataLength > 0)
		{
			//printf("Message recieved from license server: %s!\n", buffer);

			if (buffer[0] == 0x02) //opcode get item data
			{

			}
		}

		Sleep(1000);
	}

	closesocket(p->Socket);
	WSACleanup();
	shutdown(p->Socket, 0);
}

bool NetLogger::TransactHeartbeat()
{
	this->HeartbeatApproved = false;

	WSADATA wsaData;
	SOCKET Socket = INVALID_SOCKET;
	SOCKADDR_IN SockAddr;

	std::string HWID = this->FillHardwareID(); //part of final sent packet

	unsigned char buffer[256] = { 0 };

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		return false;
	}

	Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	SockAddr.sin_addr.S_un.S_addr = inet_addr(GetUnpackedServerIP().c_str());
	SockAddr.sin_port = htons(5445);
	SockAddr.sin_family = AF_INET;

	if (connect(Socket, (SOCKADDR*)(&SockAddr), sizeof(SockAddr)) != 0)
		return false;

	byte Heartbeat[] = { 0x01, 0x02, 0x03, 0x04 };

	byte* CipherHWID = NetCipher::CipherString((char*)Heartbeat); //encipher bytes
	int CipherLen = 4;

	int BytesSent = send(Socket, (const char*)CipherHWID, CipherLen, 0);

	int nDataLength = 1;

	while ((nDataLength = recv(Socket, (char*)this->HeartbeatRecvBytes, 256, 0)) == 0); //this will loop forever in the case of no reply... guess we can leave this intentional

	//start conditional ... maybe throw back hwid and do comparison once again and test for true or false finally?
	if (nDataLength == BytesSent)
	{
		if ((this->HeartbeatRecvBytes[0] == Heartbeat[0] * 2) && (this->HeartbeatRecvBytes[1] == Heartbeat[1] * 2) && (this->HeartbeatRecvBytes[2] == Heartbeat[2] * 2) && (this->HeartbeatRecvBytes[3] == Heartbeat[3] * 2))					
			this->HeartbeatApproved = true;					
	}

	closesocket(Socket);
	WSACleanup();
	return this->HeartbeatApproved;
}

int NetLogger::SendData(string data)
{
	this->HeartbeatApproved = false;

	WSADATA wsaData;
	SOCKET Socket = INVALID_SOCKET;
	SOCKADDR_IN SockAddr;

	unsigned char buffer[256] = { 0 };

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		return false;
	}

	Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	SockAddr.sin_addr.S_un.S_addr = inet_addr(GetUnpackedServerIP().c_str());
	SockAddr.sin_port = htons(5445);
	SockAddr.sin_family = AF_INET;

	if (connect(Socket, (SOCKADDR*)(&SockAddr), sizeof(SockAddr)) != 0)
		return false;

	byte opcode = 2;
	byte* packet = new byte[1 + strlen(data.c_str())];
	packet[0] = opcode;
	strcpy((char*)&packet[1], data.c_str());

	byte* CipherData = NetCipher::CipherString((char*)packet); //encipher bytes
	int CipherLen = strlen(data.c_str()) + sizeof(byte);

	int BytesSent = send(Socket, (const char*)CipherData, CipherLen, 0); //no response needed here?

	closesocket(Socket);
	WSACleanup();
	return BytesSent;
}


//WARNING: will fail if windows is not on C:/...
string NetLogger::FillHardwareID()
{
	string HWID;

	CHAR volumeName[MAX_PATH + 1] = { 0 };
	CHAR fileSystemName[MAX_PATH + 1] = { 0 };
	DWORD serialNumber = 0;
	DWORD maxComponentLen = 0;
	DWORD fileSystemFlags = 0;

	if (GetVolumeInformationA("C:\\", volumeName, ARRAYSIZE(volumeName), &serialNumber, &maxComponentLen, &fileSystemFlags, fileSystemName, ARRAYSIZE(fileSystemName)))
	{
		CHAR serialBuf[20];
		_itoa_s(serialNumber, serialBuf, 10);

		CHAR username[1024];
		DWORD size = 1024;
		GetUserNameA((CHAR*)username, &size);

		HWID = username;
		HWID += "-";
		HWID += serialBuf;
		HWID += '\0';
	}
	else
	{
		HWID = "Failed to generate HWID.";
		return NULL;
	}

	return HWID;
}

string NetLogger::GetUnpackedServerIP()
{
	char unpackedIP[15] = { 0 };

	for (int i = 0; i < strlen((const char*)serverIP); i++)
	{
		unpackedIP[i] = (serverIP[i] ^ unpackKey);
	}
	
	return "127.0.0.1";
	//return string(unpackedIP);
}

BOOL NetLogger::SendPCInfo()
{
	string user = OS::GetCurrentUsername();
	int cpuid = OS::GetCPUID();

	return true;
}