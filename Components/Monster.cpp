#include "Monster.hpp"

int Monster::GetLevel(Entity* e)
{
	UINT64 MonsterComponent = e->GetComponentAddress("Monster");

	if (MonsterComponent == NULL)
	{
		printf("MonsterComponent was NULL!\n");
		return 0;
	}

	UINT64 InternalPtr = DereferenceSafe<UINT64>(MonsterComponent + Monster::InternalPtrOffset);

	if (InternalPtr != NULL)
	{
		int Level = DereferenceSafe<int>(MonsterComponent + Monster::InternalStruct::LevelOffset);
		return Level;
	}

	return 0;
}

std::string Monster::GetName(Entity* e)
{
	UINT64 MonsterComponent = e->GetComponentAddress("Monster");

	if (MonsterComponent == NULL)
	{
		printf("MonsterComponent was NULL!\n");
		return 0;
	}

	UINT64 InternalPtr = DereferenceSafe<UINT64>(MonsterComponent + Monster::InternalPtrOffset);

	if (InternalPtr != NULL)
	{
		UINT64 VarietiesAddr = DereferenceSafe<UINT64>(InternalPtr + Monster::InternalStruct::VarietiesPtrOffset);

		if (VarietiesAddr != NULL)
		{
			char* name = DereferenceSafe<char*>(VarietiesAddr + Monster::Varieties::MonsterNameOffset);
			if (name != NULL)
			{
				std::string strName = std::string(name);
				return strName;
			}
		}		
	}

	return 0;
}

bool Monster::IsSummoned(Entity* e)
{
	UINT64 MonsterComponent = e->GetComponentAddress("Monster");

	if (MonsterComponent == NULL)
	{
		printf("MonsterComponent was NULL!\n");
		return false;
	}

	UINT64 InternalPtr = DereferenceSafe<UINT64>(MonsterComponent + Monster::InternalPtrOffset);

	if (InternalPtr != NULL)
	{
		UINT64 VarietiesAddr = DereferenceSafe<UINT64>(InternalPtr + Monster::InternalStruct::VarietiesPtrOffset);

		if (VarietiesAddr != NULL)
		{
			UINT64 TypePtr = DereferenceSafe<UINT64>(VarietiesAddr + Monster::Varieties::MonsterTypeOffset);

			if (TypePtr != NULL)
			{
				bool summoned = DereferenceSafe<bool>(TypePtr + Monster::Types::IsSummonedOffset);
				return summoned;
			}
		}
	}

	return false;
}
