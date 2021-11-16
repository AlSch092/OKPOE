#pragma once
#include "PacketBuilder.hpp"
#include "Packets.hpp"
#include "Declarations.hpp"
#include "FileIO.hpp"

namespace SkillGems
{
	enum GearSlots
	{
		RIGHT_HAND = 0,
		BODY = 2,
		LEFT_HAND = 3,
		HAT = 5,
		GLOVES = 9,
		BOOTS = 10,
	};

	enum SocketLinks
	{
		TopLeft = 0,
		TopRight = 1,
		BottomRight = 2,
		BottomLeft = 3
	};

	void LevelUpSkillGem(int ItemSlot, int LinksSlot);

	// Token: 0x04004664 RID: 18020
	const UINT64 AdvanceInfoOffset = 0x20;
	const UINT64 TotalExpGainedOffset = 0x28;
	const UINT64 LevelOffset = 0x2C;
	const UINT64 ExpPrevLvlOffset = 0x30;
	const UINT64 ExpMaxLvlOffset = 0x34;
	const UINT64 QualityTypeIdOffset = 0x38;

	//For "GemInformation" structure... not sure?
	const UINT64 SocketColorOffset = 0x30;
	const UINT64 MaxLvlOffset = 0x48;
	const UINT64 LimitLevel = 0x4C;
}