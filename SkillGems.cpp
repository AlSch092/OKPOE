#include "SkillGems.hpp"

void SkillGems::LevelUpSkillGem(int ItemSlot, int SkilLGemIndex, int LinksSlot)
{
	PacketWriter* p = PacketBuilder::LevelUpSkillGem(ItemSlot, SkilLGemIndex, LinksSlot); //this 2 changes each time.. probably elementId or something
	UINT64 SendClass = GetSendClass();
	
	if (p == NULL || SendClass == NULL)
	{
		FileIO::Log("Couldn't get sendClass at LevelUpSkillGem.\n");
		return;
	}

	SendPacket(SendClass, (LPBYTE)p->GetBuffer(), p->GetSize());
	FileIO::Log("Leveled up skill gem on gear slot %d (socket slot %d, SkillGemIndex=%d).\n", ItemSlot, LinksSlot, SkilLGemIndex);
}