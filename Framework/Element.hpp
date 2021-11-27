#pragma once
#include "Pointer.hpp"

namespace Element
{
	enum Identifiers
	{

	};

	static const UINT64 IdentifierOffset = 8;
	static const UINT64 SelfPointerOffset = 0x28;
	static const UINT64 ChildsOffset = 0x30;
	static const UINT64 ChildEndOffset = 0x38;
	static const UINT64 RootOffset = 0xD8;
	static const UINT64 ParentOffset = 0xE0;
	static const UINT64 XOffset = 0xE8;
	static const UINT64 YOffset = 0xEC;
	static const UINT64 ScaleOffset = 0x158;
	static const UINT64 IsVisibleLocalOffset = 0x161;

	static const UINT64 ElementBorderColorOffset = 0x160;
	static const UINT64 ElementBackgroundColorOffset = 0x164;
	static const UINT64 ElementOverlayColorOffset = 0x168;

	static const UINT64 WidthOffset = 0x180;
	static const UINT64 HeightOffset = 0x184;

	static const UINT64 TextBoxBorderColorOffset = 0x190;
	static const UINT64 TextBoxOverlayColorOffset = 0x194;

	static const UINT64 HighlightBorderColorOffset = 0x1c0;
	static const UINT64 isHighlightedOffset = 0x1C3;

	static const UINT64 TooltipOffsetOffset = 0x3E8;

	static const UINT64 EntityOffset = 0x428; //if this is present, we are an inventory item, or an item?
	static const UINT64 CellXOffset = 0x430;
	static const UINT64 CellYOffset = CellXOffset + 4;
	static const UINT64 CellWidthOffset = 0x438;
	static const UINT64 CellHeightOffset = CellWidthOffset + 4;
	static const UINT64 IsHoveredOffset = 0x496;

	void PrintHoveredElements(); 
	void GetAllElements();
	UINT64 GetChildElement(UINT64 StartingElement);
	UINT64 GetChildElementAtIndex(int index);
};
