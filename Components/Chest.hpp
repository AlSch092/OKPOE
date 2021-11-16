#pragma once
#include "Entity.hpp"

namespace Chest 
{
	static const UINT64 StrongboxInfoOffset = 0x20; //0x20
	static const UINT64 IsDestroyingAfterOpeningOffset = StrongboxInfoOffset + 0x20; //(StrongBoxInfo + 0x20) == 1 and if addr != 0
	static const UINT64 IsLargeBoxOffset = StrongboxInfoOffset + 0x21; //(StrongBoxInfo + 0x21) == 1
	static const UINT64 IsBreakableOffset = StrongboxInfoOffset + 0x22; //(StrongboxInfo + 0x22) == 1
	static const UINT64 IsOpenOnDamageTakenOffset = StrongboxInfoOffset + 0x25; //StrongboxData + 0x25 == 1
	static const UINT64 IsOpenWhenMonstersDieOffset = StrongboxInfoOffset + 0x28; //strongboxInfo + 0x28 == 1

	static const UINT64 IsOpenedOffset = 0x58; // 0x58 == 1
	static const UINT64 IsLockedOffset = 0x59; //0x59 > 1
	static const UINT64 IsStrongboxOffset = 0x98; //0x98 > 0
	static const UINT64 QualityOffset = 0x5C; //0x5C


	bool IsOpened(Entity* e);
	bool IsLocked(Entity* e);
	bool IsStrongbox(Entity* e);
	byte GetQuality(Entity* e);
};