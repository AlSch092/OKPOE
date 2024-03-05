#pragma once
#include <stdint.h>
#define OPCODE const uint16_t

namespace SendOpcodes
{
	OPCODE Tick = 0x0100;
	OPCODE Ping = 0x0F00;

	OPCODE SelectCharacter = 0x0D00;

	OPCODE PlayerChat = 0x0800; //also sent in login server when going back 2 char screen
	OPCODE SystemCommand = 0x0900;
	OPCODE ClickInventoryItem = 0x1B00;
	OPCODE PlaceInventoryItem = 0x1D00; //00 1D 00 00 00 2* 00 00 00 00 00 00 00 00 00 <- make item go poof
	OPCODE PlaceSkillGemInSocket = 0x2200;
	OPCODE LevelUpSkillGem = 0x2300;
	OPCODE ApplyPassiveSkill = 0x2500;
	OPCODE Flask = 0x5500;
	OPCODE UseItemOnItem = 0x5600;
	OPCODE ShiftClickUseItemOnItem = 0x5700;

	OPCODE ConsumeInventoryItem = 0x4300; //use portal scroll to get
	OPCODE DropItem = 0x1C00; //no data


	OPCODE InventoryToStash = 0xB200; //00 B2 00 05 00 00 00 0B 00 8C B4 
	OPCODE InventoryToStashWithAffinity = 0xB300; //00 B3 00 00 00 40 00 00 00 01 00 01 01 
	OPCODE StashToInventory = 0xB500; //00 B5 00 01 00 00 00 10 00 5B B3 

	OPCODE InventoryUnk1 = 0xA800;
	OPCODE AutoPlaceItemFromStash = 0xAF00;
	OPCODE InventoryToMapWindow = 0xB600; //needed for map botting
	OPCODE InventoryToGuildTagWindow = 0xCB00;

	OPCODE MoveItemControlClick = 0xBA00;

	OPCODE PredictiveInteraction = 0x1700;
	OPCODE PredictiveInput = 0x1800;

	OPCODE PlayerInput = 0x4001;
	OPCODE EntityInteraction = 0x4101;
	OPCODE CastAuraSkill = 0x4201; //for skills supported by blaphemy support, 01 42 00 00 01 74 00 00 01 8E 80 03 , but we can just use self skill and it will work
	OPCODE PlayerSelfSkill = 0x4301; //01 31 00 00 03 C7 A7 97  bone barrier. these dont require end action
	OPCODE PlayerInputContinuous = 0x4401;
	OPCODE PlayerStopInput = 0x4601;

	OPCODE LockstepInput = 0x0018;
	OPCODE LockstepInteraction = 0x0017;

	OPCODE EnterPlayerHideout = 0x3201; //01 32 00 0A 4F 6F 67 61 42 6C 6F 6F 67 61 00 00 00 3B
	OPCODE ChangeHideout = 0xE401; //01 E4 00 11   , 0x80 as third byte = guild

	OPCODE BlightTower = 0xCF01;

	OPCODE StartDelveInstance = 0xBC01;
	OPCODE ToAzuriteMines = 0x2701;
	OPCODE UpgradeDelveStat = 0xA301;
	OPCODE RefillDelveGoods = 0xA401;

	OPCODE AscendCharacter = 0x2900;
	OPCODE UseWaypoint = 0x3B00; //as of 3.17.0
	OPCODE ReviveCharacter = 0x4000;
	OPCODE JoinInstance = 0x7D00;
	OPCODE ExitToCharacterScreen = 0xFC00;
	OPCODE ExitToLoginScreen = 0x0D00;

	OPCODE CreateParty = 0x6B00;
	OPCODE PartyInvite = 0x6600;
	OPCODE CancelPartyInvite = 0x6700;
	OPCODE ExitParty = 0x6900;

	OPCODE TradePlayer = 0x8000;
	OPCODE CancelTrade = 0x7900;
	OPCODE PlaceItemNPCTrade = 0x7A00;
	OPCODE RetractNPCTradeItem = 0x7B00;
	OPCODE AcceptTrade = 0x7C00;

	OPCODE InventoryToDivinationWindow = 0xAC00; //00 AB 00 00 00 04 [00] in_out 

	OPCODE SelectNPCDialog = 0x5900;
	OPCODE ExitNPCDialog = 0x5C00;

	OPCODE PlaceExplosive = 0x2002;

	OPCODE LaunchAtlasMap = 0xAA00; //00 A4 00 1C 08 00 

	OPCODE ChangeCurrentStashTab = 0x9900; //is sent on stash interaction, not sending this might ban

	OPCODE PrepareHarvestExtractor = 0xFB01;
	OPCODE HarvestCraft = 0xF601;

	OPCODE CreateItemStack = 0x5300;

	OPCODE ChoosePantheonGod = 0x7A01;
	OPCODE LoadedNewArea = 0x7C01;

	OPCODE EventAction = 0x2702; //02 27 00 77 00 08 00 52 04 00 00 02 FD D3 
	OPCODE InterrogateSyndicateMember = 0xBF01; // 01 BF 07 01 00
	OPCODE AutomoveItem = 0xB100;
	OPCODE CraftUnveilItem = 0xB901;
	OPCODE SelectCraftVeilOption = 0xBB01; //01 BB 02

	OPCODE UseItemOnOtherItem = 0x4A00; //00 48 [00 00 00 01 ] [00 00 00 31] [00 00 00 01] [00 00 00 24]  
	OPCODE UseItemOnMap = 0x4B00; //00 4B CB E6 02 D3 00 00 00 01 00 00 00 27 00 00 00 00 4B 00 37 00 00 , 00 4B 91 10 49 3F 00 00 00 01 00 00 00 62 00 00 00 00 4B 00 05 00 00 

	OPCODE OpenKiracMapMission = 0x3400; //00 34 00 00 00 00  then 00 34 xx xx xx xx 

	OPCODE StartHeistMission = 0x0201; // 01 fc 01 00
	OPCODE HeistInteraction = 0x0202; //01 fd (entity id)
	OPCODE RevealBlueprintRoom = 0x0502; //02 05 00 04 00
	OPCODE ConfirmBlueprintPlans = 0x0602; //02 06
	OPCODE HeightBlueprintSelectTeam = 0x0702; //02 07 00 03 02 FF FF 
	OPCODE InventoryToHeistInventoryWindow = 0xC000; //00 C0 00 00 00 25 03 01 

	OPCODE ClickMapBossBuff = 0x1202;

	OPCODE StoreSentinelItem = 0xC700;
	OPCODE CombineSentinelItems = 0x1802; // 02 18 00 00 00 49 00 00 00 03 00 00 00 4A 00 00 00 09 00 00 00 01 00 00 00 21 

	OPCODE ToggleSentinelEntity = 0x3102; //02 31 00 7C 00 02 00 00 
	OPCODE ApplySentinelMapPathway = 0x1A02; //02 19 1* 00 01 02 02 01 01 00 00 00 00 00 CD B6 1D 00, 02 19 13 00 01 02 12 02 02 01 01 01 01 01 CD B6 1D 00  

	OPCODE EndDeliriumEvent = 0xF501;
	OPCODE EndBlightEvent = 0xE301;

	OPCODE JoinChatChannel = 0xE400; //00 E4 00 03 00 01 00 

	OPCODE BeginAspirantsTrial = 0x9201; //01 92 34 
	OPCODE DivineFont = 0xC401; //01 C4 23 5B 

	OPCODE TeleportPartyMember = 0x6B00; //00 6B 00 0C 46 72 65 73 68 45 78 70 52 75 73 68 

	OPCODE UpdateGuildTag = 0x0401;

	OPCODE FinishedTrial = 0xE301; //00 E3 01 , sent on hitting stone at end of lab trials

	OPCODE MetamorphButtonReady = 0x0802; //02 08
	OPCODE SpawnMetamorphBoss = 0x0A02; //02 0A 00 00 00 03 00 00 00 06 00 00 00 0D 00 00 00 32 00 00 00 72 

	OPCODE CraftBeastiary = 0xAD01; //01 AD 00 05
	OPCODE SelectBeastiaryMonster = 0xAF01; //01 AF 00 00 0E 00 36 F0 2A 83 , 01 AF 04 22 00 42 00 0B 00 05 00 00 0E 01 53 FB F9 52 

	OPCODE StartReverseIncursion = 0x2E02; //02 2e 00

	OPCODE SplitCrucibleItem = 0x3102; //02 31 00 00 00 04 00 00 00 08 00 00 00 01 00 00 00 2C 
	OPCODE AddCrucibleUniqueItem = 0x3302; //02 33 00 00 00 03 00 00 00 0A 
}