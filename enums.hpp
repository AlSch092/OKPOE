#pragma once

namespace enums
{
	enum Hideouts //todo: get rest
	{
		Cartographer = 0x11,
		NONE = 0x00
	};

	enum LabTrials
	{
		First = 1,
		Cruel = 2,
		Merciless = 3,
		Eternal = 4,
		Fortune = 0x14,
		Opportunity = 0x15, //check this
		Potential = 0x34,
	};

	enum DivineFonts
	{
		Add45to68FireDamage_Boots = 0x5B23,
		WordOfReflection_Gloves = 0x609B
	};

	enum AtlasModsSelection
	{
		OnePercentQuantity = 0x1C,

		Regular = 0x1E,
		FortuneFavorsTheBraveUniqueMap = 0x20,
		ApexOfSacrifice = 0x21,
		FortuneFavorsTheBrave = 0x24, //takes chaos
		TwelveRogueExiles = 0x29,
		TenMobPacksNemesis = 0x2A,
		SixShrines = 0x2B,
		SixMobPacksBloodlineMod = 0x2C,
		KillStreakRampage = 0x2D,
		SixStrongboxes = 0x2E,
		FiveHarbingers = 0x2F,
		CorruptingTempest = 0x30,
		MonstrousTreasure = 0x31,
		AlluringVaalSideArea = 0x32,
		LabWithImprovedOffering = 0x33,
		AdditionalBreach = 0x34,
		ThreeShrines = 0x35,
		ThreeEssences = 0x36,
		FourShrines = 0x37,
		MetamorphMonsters = 0x38,
		NoModsOrFragments = 0xFFFF,

	};

	enum AtlasMasterMods
	{
		Einhar = 2,
		Alva = 3,
		Niko = 5,
		Syndicate = 6,
		Cassia = 9,

		Expedition = 11,

	};//00 9B 00 1E 06 00 last byte adds maven to map

	enum AtlasSpawnAddons
	{
		Maven = 1,
	};

	enum SyndicateMembers
	{
		Haku = 1,
		Hillock = 6,
		Leo = 7,
		Guff = 8,
		Janus = 9,
		Korell = 13,
		Aisling = 16
	};

	enum PantheonGods
	{
		BRINE_KING = 1,
		ARAKAALI = 2,
		SOLARIS = 3,
		LUNARIS = 4,
		GRUTHKUL = 9,
		SHAKARI = 11,
		TUKOHAMA = 12,
		RALAKESH = 13,
	};

	//Metadata/Monsters/LeagueBlight/BlightTowerFlame@70
	enum BlightTowers
	{
		ICE_T1 = 1,
		ICE_T2,
		ICE_T3,
		ICE_T4,
		ICE_T5,
		LIGHTNING_T1 = 5,
		LIGHTNING_T2 = 6,
		LIGHTNING_T3 = 7,
		LIGHTNING_T4 = 8,
		LIGHTNING_T5 = 9,
		FIRE_T1 = 0x1A,
		FIRE_T2 = 0x1B,
		FIRE_T3 = 0x1C,
		FIRE_T4 = 0x1D,
		FIRE_T5 = 0x1E,
		PHYSICAL_T1,
		PHYSICAL_T2,
		PHYSICAL_T3,
		PHYSICAL_T4,
		PHYSICAL_T5,
		EMPOWERING_T1,
		EMPOWERING_T2,
		EMPOWERING_T3,
		EMPOWERING_T4,
		EMPOWERING_T5,
		SUMMON_T1,
		SUMMON_T2,
		SUMMON_T3,
		SUMMON_T4,
		SUMMON_T5
	};

	enum Inventories
	{
		Player = 1,
		CurrencyTab = 0x49,
	};

	enum Windows
	{
		TradeWindowLocal = 5,
		TradeWindowRemote = 6,
	};

	enum SystemMessages
	{
		TotalTimePlayed = 2,
		CreationDate = 3,
		QueryMonstersRemaining = 4,
		TimesDied = 5,
		PVPStats = 6,
		Rankings = 7,
		DestroyCursorItem = 9, //weird
		WhoIsCharacter = 10,
		GetCursorItemLevel = 12,
		ChangeCursorItemVisualIdentity = 13,
		SendBugReport = 14,

	};

	enum CreatureType
	{
		Actor = 13,
		Minion = 1,
		Basic = 2,
		Magic = 4,
		Rare = 7,
		Unique = 10
	};

}