#include "Autotrader.hpp"

using namespace Inventory;

extern AutoPlayer* Robot;

//Most functions here ommitted from public to stop mass tradebots..
void AutoBuy()
{
}

bool IsCurrencyItem(wstring cname)
{
	const wchar_t* str = cname.c_str();
	bool isCurrency = false;

	if (str != NULL)
	{
		if (str == L"Chaos Orb" || iequals(cname, L"chaos") || iequals(cname, L"chaos orb"))
			isCurrency = true;
		else if (str == L"Orb of Alchemy" || iequals(cname, L"alchemy") || iequals(cname, L"orb of alchemy"))
			isCurrency = true;
		else if (str == L"Orb of Alteration" || iequals(cname, L"alchemy"))
			isCurrency = true;
		else if (str == L"Orb of Fusing" || iequals(cname, L"fusing"))
			isCurrency = true;
		else if (str == L"Vaal Orb" || iequals(cname, L"vaal"))
			isCurrency = true;
		else if (str == L"Exalted Orb" || iequals(cname, L"exalted"))
			isCurrency = true;
		else if (str == L"Jeweller's Orb" || iequals(cname, L"jeweller's"))
			isCurrency = true;
		else if (str == L"Gemcutter's Prism" || iequals(cname, L"gcp"))
			isCurrency = true;
		else if (str == L"Divine Orb" || iequals(cname, L"divine"))
			isCurrency = true;
		else if (str == L"Chromatic Orb" || iequals(cname, L"chromatic"))
			isCurrency = true;
		else if (str == L"Orb of Chance" || iequals(cname, L"chance"))
			isCurrency = true;
		else if (str == L"Cartographer's Chisel" || iequals(cname, L"chisel"))
			isCurrency = true;
		else if (str == L"Orb of Scouring" || iequals(cname, L"scouring"))
			isCurrency = true;
		else if (str == L"Blessed Orb" || iequals(cname, L"blessed"))
			isCurrency = true;
		else if (str == L"Orb of Regret" || iequals(cname, L"regret"))
			isCurrency = true;
		else if (str == L"Regal Orb" || iequals(cname, L"regal"))
			isCurrency = true;
		else if (str == L"Glassblower's Bauble" || iequals(cname, L"bauble"))
			isCurrency = true;
		else if (str == L"Orb of Transmutation" || iequals(cname, L"transmutation"))
			isCurrency = true;
		else if (str == L"Orb of Augmentation" || iequals(cname, L"augmentation"))
			isCurrency = true;
		else if (str == L"Mirror of Kalandra" || iequals(cname, L"mirror"))
			isCurrency = true;
		else if (str == L"Eternal Orb" || iequals(cname, L"eternal"))
			isCurrency = true;
		else if (str == L"Silver Coin" || iequals(cname, L"silver"))
			isCurrency = true;
		else if (iequals(cname, L"simple sextant"))
			isCurrency = true;
		else if (iequals(cname, L"prime sextant"))
			isCurrency = true;
		else if (iequals(cname, L"awakened sextant"))
			isCurrency = true;
		else if (iequals(cname, L"elevated sextant"))
			isCurrency = true;
		else if (iequals(cname, L"orb of annulment") || iequals(cname, L"annulment"))
			isCurrency = true;
		else if (str == L"Orb of Binding" || iequals(cname, L"binding"))
			isCurrency = true;
		else if (str == L"Orb of Horizons" || iequals(cname, L"horizons"))
			isCurrency = true;
		else if (str == L"Harbinger's Orb" || iequals(cname, L"harbinger's"))
			isCurrency = true;
		else if (str == L"Ancient Orb" || iequals(cname, L"ancient"))
			isCurrency = true;
		else if (str == L"Mirror Shard" || iequals(cname, L"mirror shard"))
			isCurrency = true;
		else if (str == L"Chaos Shard" || iequals(cname, L"chaos shard"))
			isCurrency = true;
		else if (str == L"Exalted Shard" || iequals(cname, L"exalted shard"))
			isCurrency = true;
		else if (str == L"Annulment Shard" || iequals(cname, L"annulment shard"))
			isCurrency = true;
		else if (str == L"Beastiary Orb" || iequals(cname, L"beasiary"))
			isCurrency = true;
		else if (str == L"Instilling Orb" || iequals(cname, L"instilling"))
			isCurrency = true;
		else if (str == L"Enkindling Orb" || iequals(cname, L"enkindling"))
			isCurrency = true;
		else if (str == L"Blacksmith's Whetstone" || iequals(cname, L"blacksmith's whetstone"))
			isCurrency = true;
	}

	return isCurrency;
}

bool iequals(const wstring& a, const wstring& b)
{
	unsigned int sz = a.size();
	if (b.size() != sz)
		return false;
	for (unsigned int i = 0; i < sz; ++i)
		if (towlower(a[i]) != towlower(b[i]))
			return false;
	return true;
}

void AutoSell()
{

}

BOOL CurrencyStashToInventory(std::wstring itemBaseName, int StackSize, int PlaceInX, int PlaceInY)
{
	return FALSE;
}

//change this from entity name to unique name??
BOOL StashToInventory(std::wstring EntityName, int tab, bool isCurrencyTab) //change this away from [0], add tab param
{
	return FALSE;
}

wstring PriceNameToItemName(wstring priceTagName) //finish this
{
	wstring realName;
	return realName;
}

BOOL DoTradeWindowItemsMeetPrice(wstring priceTag) //"~price %d %s"     
{
	return FALSE;
}

void SearchItems(const char* server, const char* itemName, const char* buyoutCurrency, int buyoutMax) //todo: slowly add in all params lol
{
}

void SearchCurrencyItems(const char* server, const char* itemNameHave, const char* itemNameWant, int buyoutMax)
{
}


