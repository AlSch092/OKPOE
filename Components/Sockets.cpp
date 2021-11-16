#include "Sockets.hpp"

int Sockets::GetNumberOfSockets(Entity* e)
{
	UINT64 SocketsComponentAddr = e->GetComponentAddress("Sockets");
	
	int nSockets = 0;

	if (SocketsComponentAddr == 0)
	{
		return 0;
	}

	printf("Sockets addr: %llX\n", SocketsComponentAddr);

	int Count = 0;
	int Colors[6]; //max 6..

	for (int i = 0; i < 6; i++)
	{
		int nSocket = DereferenceSafe<int>(SocketsComponentAddr + Sockets::SocketsOffset + (i * 4));
		if (nSocket > 0)
		{
			Colors[i] = nSocket;
			Count += 1;
		}
	}

	return Count;
}

int* Sockets::GetSocketTypes(Entity* e)
{
	UINT64 SocketsComponentAddr = e->GetComponentAddress("Sockets");

	int nSockets = 0;

	if (SocketsComponentAddr == 0)
	{
		return 0;
	}

	int Count = 0;
	int* Colors = new int[6]; //max 6..

	for (int i = 0; i < 6; i++)
	{
		int nSocket = DereferenceSafe<int>(SocketsComponentAddr + Sockets::SocketsOffset + (i * 4));
		if (nSocket > 0)
		{
			Colors[i] = nSocket;
			Count += 1;
		}
	}

	return Colors;
}

int Sockets::GetSocketLinks(Entity* e)
{
	UINT64 SocketsComponentAddr = e->GetComponentAddress("Sockets");
	
	int nSockets = 0;

	if (SocketsComponentAddr == 0)
	{
		return 0;
	}

	printf("Sockets: %llX\n", SocketsComponentAddr);
	int Count = 0;
	int Colors[6]; //max 6..

	for (int i = 0; i < 6; i++)
	{
		int nSocket = DereferenceSafe<int>(SocketsComponentAddr + Sockets::SocketsOffset + (i * 4));
		if (nSocket > 0)
		{
			Colors[i] = nSocket;
			Count += 1;
		}
	}

	UINT64 LinksAddr = SocketsComponentAddr + 0x60;
	LinksAddr = DereferenceSafe<UINT64>(LinksAddr);

	BYTE Links = DereferenceSafe<byte>(LinksAddr);
	int nLinks = 0;
	int nCount = 0;

	while (nLinks < Count)
	{
		BYTE Link = DereferenceSafe<byte>(LinksAddr + nCount);
		nLinks += Link;
		nCount += 1;
	}

	return Links; //just return first for now I guess. if Links == count we have max linked item anyways
}

bool Sockets::isItemFullyLinked(Entity* e)
{
	bool linked = false;

	if (GetSocketLinks(e) == GetNumberOfSockets(e))
	{
		linked = true;
	}

	return linked;
}