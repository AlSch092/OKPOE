#pragma once
#include "Entity.hpp"
#include "WorldItem.hpp"
#include "FileIO.hpp"

class GroundItem : public Entity
{
public:

	GroundItem(UINT64 Address)
	{
		Initialize(Address);
	}

	int ItemRarity;

	std::wstring UniqueName; //for items
	std::wstring BaseName;
	std::wstring FullName; //unique name + base name
};