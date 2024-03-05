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

	namespace Offsets
	{
		const UINT64 AdvanceInfo = 0x20;
		const UINT64 TotalExpGained = 0x28;
		const UINT64 Level = 0x2C;
		const UINT64 ExpPrevLvl = 0x30;
		const UINT64 ExpMaxLvl = 0x34;
		const UINT64 QualityTypeId = 0x38;
	}
	
	 

	void LevelUpSkillGem(int ItemSlot, int SkilLGemIndex, int LinksSlot);




	//For "GemInformation" structure... not sure?
	const UINT64 SocketColorOffset = 0x30;
	const UINT64 MaxLvlOffset = 0x48;
	const UINT64 LimitLevel = 0x4C;
}