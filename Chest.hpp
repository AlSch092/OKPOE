#pragma once
#include "Entity.hpp"

namespace Chest 
{
	namespace Offsets
	{
		static const UINT64 IsOpened = 0x170;
		static const UINT64 IsLocked = 0x171; //a strongbox gets 'locked' after opening it and before it is flagged as open.
		static const UINT64 quality = 0x174;
		static const UINT64 IsStrongbox = 0x1A0; //check
		static const UINT64 Quality = 0x5C;
	}

	namespace Strongbox //these might not really be useful at this point
	{
		namespace Offsets
		{
			static const UINT64 StrongboxInfo = 0x20; //0x20
			static const UINT64 IsDestroyingAfterOpening = StrongboxInfo + 0x20; //(StrongBoxInfo + 0x20) == 1 and if addr != 0
			static const UINT64 IsLargeBox = StrongboxInfo + 0x21; //(StrongBoxInfo + 0x21) == 1
			static const UINT64 IsBreakable = StrongboxInfo + 0x22; //(StrongboxInfo + 0x22) == 1
			static const UINT64 IsOpenOnDamageTaken = StrongboxInfo + 0x25; //StrongboxData + 0x25 == 1
			static const UINT64 IsOpenWhenMonstersDie = StrongboxInfo + 0x28; //strongboxInfo + 0x28 == 1
		}
	}

	bool IsOpened(Entity* e);
	bool IsLocked(Entity* e);
	bool IsStrongbox(Entity* e);
	byte GetQuality(Entity* e);
};