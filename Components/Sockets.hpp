#pragma once
#include "Entity.hpp"

namespace Sockets
{
	enum Colors
	{
		RED = 1,
		GREEN = 2,
		BLUE = 3
	};

	const UINT64 SocketsOffset = 0x18;
	const UINT64 LinksOffset = 0x60;

	int GetNumberOfSockets(Entity* e);
	int GetSocketLinks(Entity* e);
	int* GetSocketTypes(Entity* e); //colors
	
	bool isItemFullyLinked(Entity* e);
}