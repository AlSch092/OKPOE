#pragma once
#include "Entity.hpp"

namespace WorldItem
{
	//vars
	const UINT64 ItemOffset = 0x28; //this will be ptr to the item entity so we must make a worlditem -> Entity* func

	//functions
	Entity* GetEntityFromWorldItem(UINT64 ComponentAddr);
	Vector2 GetItemPosition(UINT64 ComponentAddr); //skips keeping track of an entity and gets the subobject positioned, since baseobj entity has none
};


namespace CurrencyFilePaths
{
	const std::wstring Wisdom = L"Metadata/Items/Currency/CurrencyIdentification";
	const std::wstring Portal = L"Metadata/Items/Currency/CurrencyPortal";
	const std::wstring Transmutation = L"Metadata/Items/Currency/CurrencyUpgradeToMagic";
	const std::wstring Augmentation = L"Metadata/Items/Currency/CurrencyAddModToMagic";
	const std::wstring Alteration = L"Metadata/Items/Currency/CurrencyRerollMagic";
	const std::wstring Scrap = L"Metadata/Items/Currency/CurrencyArmourQuality";
	const std::wstring Whetstone = L"Metadata/Items/Currency/CurrencyWeaponQuality";
	const std::wstring Glassblower = L"Metadata/Items/Currency/CurrencyFlaskQuality";
	const std::wstring Chisel = L"Metadata/Items/Currency/CurrencyMapQuality";
	const std::wstring Chromatic = L"Metadata/Items/Currency/CurrencyRerollSocketColours";
	const std::wstring Chance = L"Metadata/Items/Currency/CurrencyUpgradeRandomly";
	const std::wstring Alchemy = L"Metadata/Items/Currency/CurrencyUpgradeToRare";
	const std::wstring Jeweller = L"Metadata/Items/Currency/CurrencyRerollSocketNumbers";
	const std::wstring Fusing = L"Metadata/Items/Currency/CurrencyRerollSocketLinks";
	const std::wstring Scouring = L"Metadata/Items/Currency/CurrencyConvertToNormal";
	const std::wstring Blessed = L"Metadata/Items/Currency/CurrencyRerollImplicit";
	const std::wstring Regal = L"Metadata/Items/Currency/CurrencyUpgradeMagicToRare";
	const std::wstring Chaos = L"Metadata/Items/Currency/CurrencyRerollRare";
	const std::wstring Vaal = L"Metadata/Items/Currency/CurrencyCorrupt";
	const std::wstring Regret = L"Metadata/Items/Currency/CurrencyPassiveRefund";
	const std::wstring Gemcutter = L"Metadata/Items/Currency/CurrencyGemQuality";
	const std::wstring Divine = L"Metadata/Items/Currency/CurrencyModValues";
	const std::wstring Exalted = L"Metadata/Items/Currency/CurrencyAddModToRare";
	const std::wstring Eternal = L"Metadata/Items/Currency/CurrencyImprintOrb";
	const std::wstring Mirror = L"Metadata/Items/Currency/CurrencyDuplicate";
	const std::wstring PerandusCoin = L"Metadata/Items/Currency/CurrencyPerandusCoin";
	const std::wstring SilverCoin = L"Metadata/Items/Currency/CurrencySilverCoin";
	const std::wstring Prophecy = L"Metadata/Items/Currency/CurrencyItemisedProphecy";
	const std::wstring SimpleSextant = L"Metadata/Items/Currency/CurrencyAddAtlasMod";
	const std::wstring PrimeSextant = L"Metadata/Items/Currency/CurrencyAddAtlasModMid";
	const std::wstring AwakenedSextant = L"Metadata/Items/Currency/CurrencyAddAtlasModHigh";
	const std::wstring SealApprentice = L"Metadata/Items/Currency/CurrencySealMapLow";
	const std::wstring SealJourneyman = L"Metadata/Items/Currency/CurrencySealMapMid";
	const std::wstring SealMaster = L"Metadata/Items/Currency/CurrencySealMapHigh";
	const std::wstring Unshaping = L"Metadata/Items/Currency/CurrencyRespecShapersOrb";
	const std::wstring SplinterXoph = L"Metadata/Items/Currency/CurrencyBreachFireShard";
	const std::wstring SplinterTul = L"Metadata/Items/Currency/CurrencyBreachColdShard";
	const std::wstring SplinterEsh = L"Metadata/Items/Currency/CurrencyBreachLightningShard";
	const std::wstring SplinterUulNetol = L"Metadata/Items/Currency/CurrencyBreachPhysicalShard";
	const std::wstring SplinterChayula = L"Metadata/Items/Currency/CurrencyBreachChaosShard";
	const std::wstring BlessingXoph = L"Metadata/Items/Currency/CurrencyBreachUpgradeUniqueFire";
	const std::wstring BlessingTul = L"Metadata/Items/Currency/CurrencyBreachUpgradeUniqueCold";
	const std::wstring BlessingEsh = L"Metadata/Items/Currency/CurrencyBreachUpgradeUniqueLightning";
	const std::wstring BlessingUulNetol = L"Metadata/Items/Currency/CurrencyBreachUpgradeUniquePhysical";
	const std::wstring BlessingChayula = L"Metadata/Items/Currency/CurrencyBreachUpgradeUniqueChaos";
	const std::wstring Annulment = L"Metadata/Items/Currency/CurrencyRemoveMod";
	const std::wstring Binding = L"Metadata/Items/Currency/CurrencyUpgradeToRareAndSetSockets";
	const std::wstring Horizon = L"Metadata/Items/Currency/CurrencyRerollMapType";
	const std::wstring Harbinger = L"Metadata/Items/Currency/CurrencyUpgradeMapTier";
	const std::wstring Engineer = L"Metadata/Items/Currency/CurrencyStrongboxQuality";
	const std::wstring Ancient = L"Metadata/Items/Currency/CurrencyRerollUnique";
	const std::wstring ScrollFragment = L"Metadata/Items/Currency/CurrencyIdentificationShard";
	const std::wstring TransmutationShard = L"Metadata/Items/Currency/CurrencyUpgradeToMagicShard";
	const std::wstring AlterationShard = L"Metadata/Items/Currency/CurrencyRerollMagicShard";
	const std::wstring AlchemyShard = L"Metadata/Items/Currency/CurrencyUpgradeToRareShard";
	const std::wstring AnnulmentShard = L"Metadata/Items/Currency/CurrencyRemoveModShard";
	const std::wstring BindingShard = L"Metadata/Items/Currency/CurrencyUpgradeToRareAndSetSocketsShard";
	const std::wstring HorizonShard = L"Metadata/Items/Currency/CurrencyRerollMapTypeShard";
	const std::wstring HarbingerShard = L"Metadata/Items/Currency/CurrencyUpgradeMapTierShard";
	const std::wstring EngineerShard = L"Metadata/Items/Currency/CurrencyStrongboxQualityShard";
	const std::wstring AncientShard = L"Metadata/Items/Currency/CurrencyRerollUniqueShard";
	const std::wstring RegalShard = L"Metadata/Items/Currency/CurrencyUpgradeMagicToRareShard";
	const std::wstring ChaosShard = L"Metadata/Items/Currency/CurrencyRerollRareShard";
	const std::wstring ExaltedShard = L"Metadata/Items/Currency/CurrencyAddModToRareShard";
	const std::wstring MirrorShard = L"Metadata/Items/Currency/CurrencyDuplicateShard";
	const std::wstring DeliriumJeweller = L"Metadata/Items/Currency/CurrencyAfflictionOrbTrinkets";
	const std::wstring RemnantOfCorruption = L"Metadata/Items/Currency/CurrencyCorruptMonolith";
	const std::wstring CrusadersExaltedOrb = L"Metadata/Items/AtlasExiles/AddModToRareCrusader";
	const std::wstring WarlordsExaltedOrb = L"Metadata/Items/AtlasExiles/AddModToRareWarlord";
	const std::wstring RedeemersExaltedOrb = L"Metadata/Items/AtlasExiles/AddModToRareRedeemer";
	const std::wstring HuntersExaltedOrb = L"Metadata/Items/AtlasExiles/AddModToRareHunter";
	const std::wstring AwakenersOrb = L"Metadata/Items/AtlasExiles/ApplyInfluence";

	static void PrintAll()
	{
		//wprintf(L"%s\n", Transmutation.c_str());
		//wprintf(L"%s\n", Augmentation.c_str());
		//wprintf(L"%s\n", Alteration.c_str());
		//wprintf(L"%s\n", Scrap.c_str());
		//wprintf(L"%s\n", Glassblower.c_str());
		//wprintf(L"%s\n", AwakenersOrb.c_str());
		//wprintf(L"%s\n", Horizon.c_str());
		//wprintf(L"%s\n", Harbinger.c_str());
		//wprintf(L"%s\n", Engineer.c_str());
		//wprintf(L"%s\n", Ancient.c_str());
		//wprintf(L"%s\n", Annulment.c_str());
		//wprintf(L"%s\n", ChaosShard.c_str());
		//wprintf(L"%s\n", ExaltedShard.c_str());
		//wprintf(L"%s\n", MirrorShard.c_str());
		//wprintf(L"%s\n", Exalted.c_str());
		//wprintf(L"%s\n", Eternal.c_str());
		//wprintf(L"%s\n", Chaos.c_str());
		//wprintf(L"%s\n", Vaal.c_str());
		//wprintf(L"%s\n", Mirror.c_str());
		//wprintf(L"%s\n", Chisel.c_str());
		//wprintf(L"%s\n", Chromatic.c_str());
		//wprintf(L"%s\n", Chance.c_str());
		//wprintf(L"%s\n", Alchemy.c_str());
		//wprintf(L"%s\n", Jeweller.c_str());
		//wprintf(L"%s\n", Fusing.c_str());
		//wprintf(L"%s\n", Fusing.c_str());
		//wprintf(L"%s\n", Blessed.c_str());
		//wprintf(L"%s\n", Regal.c_str());
		//wprintf(L"%s\n", Regret.c_str());
		//wprintf(L"%s\n", Chance.c_str());
	}
}