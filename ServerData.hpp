#pragma once
#include <Windows.h>

namespace ServerPlayerData
{
	const UINT64 PassiveSkillIdsOffset = 0x170;
	const UINT64 PlayerClassOffset = 0x228;
	const UINT64 LevelOffset = 0x22C;
	const UINT64 RefundPointsOffset = 0x230;
	const UINT64 QuestPassiveSkillPointsOffset = 0x234;
	const UINT64 PassivePointsOffset = 0x238;
	const UINT64 TotalAscendencyPointsOffset = 0x23C;
	const UINT64 SpentAscendencyPointsOffset = 0x240;
}

namespace ServerData
{
	const UINT64 PlayerDataOffset = 0x718;
	const UINT64 NetworkStateOffset = 0x780;
	const UINT64 LeagueOffset = 0x798;
	const UINT64 TimeInGameOffset = 0x818;
	const UINT64 LatencyOffset = 0x830;
	
	const UINT64 GuildStashTabsOffset = 0x850;
	const UINT64 FriendsListOffset = 0x498;
	const UINT64 PendingInvitesOffset = 0x718;
	const UINT64 PartyStatusTypeOffset = 0x718;
	const UINT64 CurrencyPartyOffset = 0x718;

	const UINT64 GuildNameOffset = 0x718;
	const UINT64 SkillBarIdsOffset = 0x718;
	const UINT64 NearestPlayersOffset = 0x718;

	const UINT64 PlayerInventoriesOffset = 0x718;
	const UINT64 NPCInventoriesOffset = 0x718;
	const UINT64 GuildInventoriesOffset = 0x718;

	const UINT64 TradeChatChannel = 0x9078;
	const UINT64 GlobalChatChannel = 0x9080;
	const UINT64 LastActionIdOffset = 0x9120;
}