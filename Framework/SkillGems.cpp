#include "SkillGems.hpp"

void SkillGems::LevelUpSkillGem(int ItemSlot, int LinksSlot)
{
	PacketWriter* p = PacketBuilder::LevelUpSkillGem(ItemSlot, 2, LinksSlot);
	UINT64 SendClass = GetSendClass();
	
	if (p == NULL || SendClass == NULL)
	{
		FileIO::Log("Couldn't get sendClass at LevelUpSkillGem.\n");
		return;
	}

	SendPacket(SendClass, (LPBYTE)p->GetBuffer(), p->GetSize());
	FileIO::Log("Leveled up skill gem on gear slot %d (socket slot %d).\n", ItemSlot, LinksSlot);
}
