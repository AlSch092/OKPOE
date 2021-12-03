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

	enum SocketSlots
	{
		TopLeft = 0,
		TopRight = 1,
		BottomRight = 2,
		BottomLeft = 3
	};

	void LevelUpSkillGem(int ItemSlot, int LinksSlot);

	const UINT64 AdvanceInfoOffset = 0x20;
	const UINT64 TotalExpGainedOffset = 0x28;
	const UINT64 LevelOffset = 0x2C;
	const UINT64 ExpPrevLvlOffset = 0x30;
	const UINT64 ExpMaxLvlOffset = 0x34;
	const UINT64 QualityTypeIdOffset = 0x38;

  //struct within the other
	const UINT64 _SocketColorOffset = 0x30;
	const UINT64 _MaxLvlOffset = 0x48;
	const UINT64 _LimitLevel = 0x4C;
}
