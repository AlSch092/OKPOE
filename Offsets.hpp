#pragma once
#include <Windows.h>

namespace Offsets
{
	namespace Pointers
	{
		static UINT64 ClientVersion;

		static UINT64 PointerIngameState;

		static UINT64 MaphackPtrOfs1 = 0x428; //+1EB10A6 -> cmp byte ptr [rsi+65],00, "visibility_radius"
		static UINT64 RevealMap = 0x5C; //66 C7 47 5C 00 00 c6 47 5e 00, 80 7f 5c 00 74 05 0f 28 c7 eb 04

		static UINT64 PointerLocalEntity; //48 8B B9 08 02 00 00 48 85 DB 74 44 48 89 74 24 40 be ff ff ff ff 8b c6 f0 0f broken...
		static UINT64 LocalEntityOfs1 = 0x348;
		static UINT64 LocalEntityOfs2 = 0x9EC8; //48 8b 8f ? ? ? ? 33 d2 e8 ? ? ? ? e9 ? ? ? ? 48 8b 9f ? ? ? ?
		static UINT64 LocalEntityOfs3 = 0x8;

		static UINT64 CameraBase; //49 8b 8d d8 00 00 00 48 83 c1 40 48 8d 95 ? ? ? ? e8
		static UINT64 ZoomOffset = 0x420; //48 8b 86 ?? ?? ?? ?? f2 0f 10 44 24 64 f2 0f 11 40 5c 80 78 64 00

		static UINT64 PtrInventoryElement; //48 8b 1d ? ? ? ? 48 8b 3d ? ? ? ? 48 3b df 74 15 48 8b 0b
	}

	namespace Hacks
	{
		static UINT64 AlwaysShowLifeBars; //7C 6D 41 8B 88 ?? ?? 00 00 66 41 0F 6e 88 ?? ?? 00 00
		static UINT64 NoZoomLimits; //48 8D 44 24 20 0F 2F 11 48 0F 43 C1

		static UINT64 AntiMigrateFunction; //48 89 5c 24 08  48 89 74 24 10  57 48 83 ec 20    48 8b b9 e8 00 00 00 48 8b d9

		static UINT64 MaphackAddress; //66 C7 ?? 58 00 00 c6 ?? 5A 00

		static UINT64 GlobalLights; //0F 28 F3 F3 0f 11 49 2c 0f 57 c0 48 8d 4c 24 48

		static UINT64 UploadCrashDump; //40 55 56 48 8d ac 24 b8 f6 ff ff 48 81 ec 48 0a 00 00 broken
		static UINT64 ClientMessage; //48 89 5C 24 08 48 89 6C 24 18 56 57 41 56 B8 50 14 00 00 E8 ? ? ? ? 48 2B E0

	}

	namespace Hooks
	{
		static UINT64 SendPacket;
		static UINT64 LogSend; ///SendPacketOffset + 0x2C; //48 89 5C 24 10 48 89 74 24 20 55 57 41 56 48 8D AC 24 ? ? ? ? 48 81 ? ? ? ?
		static UINT64 LogSendReturn; ////= LogSendOffset + 0x07;

		static UINT64 EntitySpawn; //72 9F 48 8B C7 48 8B 5C 24 58 48 8B 6C 24 60 48 8B 74 24 68 48 83 c4 30 41 5F 41 5E 5F C3
		static UINT64 PortalLabelSpawn;

		static UINT64 OnSkillGemLevelUpOffset; //48 89 54 24 10 53 48 83 ec 70 48 8b d9 48 8d 15 ? ? ? ? "SkillGemLevelUp" broken
	}

	namespace IngameFunctions
	{
		static UINT64 SendPlayerCmd; //48 8b 89 ? ? ? ? 48 85 c9 0f 84 ? ? ? ? 83 bf ? ? ? ? 00 0f 8f ? ? ? ? , or go backwards from packet send. broken aob!
	}

	namespace IngameState
	{
		static UINT64 IngameStateData = 0x18; //is this game data reference?
		static UINT64 WorldData = 0x78;
		static UINT64 EntityLabelMap = 0x98; //ptr
		static UINT64 UIRoot = 0x1A0; //ptr
		static UINT64 UIHoveredElement = 0x1d8; //48 c7 87 ? ? ? ? 00 00 00 00 48 8b bb ?? ?? ?? ?? 48 8b 9b ?? ?? ?? ?? 48 3b df 74 ?? 48 8b 0b
		static UINT64 IngameUI = 0x450; //ptr
		static UINT64 UIHoverPosition = 0x1E0; //x and y
		static UINT64 UIHoverTooltip = 0x1E8; //ptr
		static UINT64 MousePositionX = 0x57C; //float
		static UINT64 MousePositionY = MousePositionX + 4;
		static UINT64 DiagnosticInfoType = 0x620; //int
		static UINT64 TimeInGameF = 0x40c; //float, time since last frame in seconds
		static UINT64 TimeInGame = TimeInGameF + 4; //float
		static UINT64 LatencyRectangle = 0x850; //long
		static UINT64 Camera = 0x870; //int
		static UINT64 FrameTimeRectangle = 0xCF0; //ptr long
		static UINT64 FPSRectangle = 0xF40; //ptr
	}

	namespace Inventory
	{
		static UINT64 MoveItemHoverState = 0x228;
		static UINT64 HoverItemPtr = 0x230;
		static UINT64 FakeCellX = 0x238;
		static UINT64 FakeCellY = 0x23C;
		static UINT64 RealCellX = 0x240;
		static UINT64 RealCellY = 0x244;
		static UINT64 CursorInventory = 0x250;
		static UINT64 ItemCount = 0x3D8;
		static UINT64 TotalSquaresInInventoryRow = 0x4C0;
	}

	namespace Element
	{
		static const UINT64 SelfPointer = 0x28;
		static const UINT64 ChildsOffset = 0x30;
		static const UINT64 ChildEndOffset = 0x38;
		static const UINT64 RootOffset = 0xD8;
		static const UINT64 ParentOffset = 0xE0;
		static const UINT64 XOffset = 0xE8;
		static const UINT64 YOffset = 0xEC;
		static const UINT64 ScaleOffset = 0x158;
		static const UINT64 IsVisibleLocal = 0x161;

		static const UINT64 ElementBorderColor = 0x160;
		static const UINT64 ElementBackgroundColor = 0x164;
		static const UINT64 ElementOverlayColor = 0x168;

		static const UINT64 WidthOffset = 0x180;
		static const UINT64 HeightOffset = 0x184;

		static const UINT64 TextBoxBorderColor = 0x190;
		static const UINT64 TextBoxOverlayColor = 0x194;

		static const UINT64 HighlightBorderColor = 0x1c0;
		static const UINT64 isHighlighted = 0x228;

		static const UINT64 TypeOffset = 0x27C; //could be wrong

		static const UINT64 Tooltip = 0x3E8;

		static const UINT64 Label = 0x328; //offset 2: 8
		static const UINT64 Label_2 = 0x08;
		static const UINT64 LabelCharacterCount = 0x334;

		static const UINT64 Entity = 0x438; //for items, atleast
	}
}

namespace HookBytes
{
	static const char* SpawnOffsetPattern = "\x48\x83\xC4\x50\x41\x5E"; //"\x48\x89\x54\x24\x10";
	static const char* LabelSpawnOffsetPattern = "\x90\x48\x8B\x44\x24\x48";
	static const char* LightsOffsetPattern = "\x0F\x28\xF3";
	static const char* CPUReducerPattern = "\x49\x83\xC0\x04\x89\x41\x20\x49\x8B\xD2";
	static const char* LevelUpSkillGemPattern = "\x40\x53\x48\x83\xEC\x50";
}