#include "Addresses.hpp"

MemoryLocations** FillAddresses(UINT64 PoEBase)
{
	MemoryLocations** Addresses = (MemoryLocations**)malloc(sizeof(MemoryLocations*) * 32);

	for (int i = 0; i < 32; i++)
	{
		Addresses[i] = new MemoryLocations;
	}

	if (PoEBase != 0)
	{
		Addresses[0]->Name = new CHAR[32];
		strncpy(Addresses[0]->Name, "Reveal Map", size_t(32));
		Addresses[0]->Offset = Offsets::MaphackAddressOffset;
		Addresses[0]->Address = g_POEBase + Addresses[0]->Offset;

		Addresses[1]->Name = new CHAR[32];
		strncpy(Addresses[1]->Name, "Log Packets", size_t(32));
		Addresses[1]->Offset = Offsets::SendPacketFuncOffset;
		Addresses[1]->Address = g_POEBase + Addresses[1]->Offset;

		Addresses[2]->Name = new CHAR[32];
		strncpy(Addresses[2]->Name, "PlayerCmd", size_t(32));
		Addresses[2]->Offset = Offsets::SendPlayerCmdOffset;
		Addresses[2]->Address = g_POEBase + Addresses[2]->Offset;

		if (Addresses[0]->Address != 0 && Addresses[0]->Address != Addresses[0]->Offset) //check if base wasn't added to offset
			return Addresses;
	}
	else
	{
		//LOG("g_POEBase == 0)"
		return nullptr;
	}

	return nullptr; //control should never get here, compiler throws warning.
}