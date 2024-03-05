#include "Autotrader.hpp"

using namespace Inventory;

extern AutoPlayer* g_Robot;

void AutoBuy()
{
	//SearchItems(server.c_str(), TheirItemName.c_str(), buyoutCurrency.c_str(), MaxSpendableQuantity);
	if (IsCurrencyItem(g_Robot->AutoTrade->TheirItemName))
	{
		g_Robot->AutoTrade->UsingCurrencyMarket = true;
	}

	//put whisper file into a list
	//Listings = PopulateListings();
	

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
	int requestedElementIndex = 0;
	bool inventoryContainsItem = false;
	bool stashContainsItem = false;
	bool stashFound = false;
	Entity* stash = NULL;
	wstring Price;


	wprintf(L"playerName: %s\n", g_Robot->AutoTrade->TradingPlayerName.c_str());
	wprintf(L"Our item name: %s \n", g_Robot->AutoTrade->OurItemName.c_str());
	wprintf(L"Their item name: %s\n", g_Robot->AutoTrade->TheirItemName.c_str());

	//interact with the stash firstly
	for each(Entity* e in g_Robot->EntityList)
	{
		if (wcscmp(e->GetFilePathFromMemory(), L"Metadata/MiscellaneousObjects/Stash") == 0)
		{
			stashFound = true;
			stash = e;
		}
	}

	if (!stashFound)
	{
		printf("Could not find a stash entity. Please log entities, re-enter map and try again.\n");
		g_Robot->AutoTrade->IsInTrade = false;
		return;
	}

	g_Robot->Interaction(stash->GetUniqueID(), 0x0266);
	
	Sleep(3000);

	//is our itemname a base name or a unique name?
	bool isRequestedItemNameABaseName = false;
	bool usingItemFullName = false;

	if (IsCurrencyItem(g_Robot->AutoTrade->OurItemName))
	{
		wprintf(L"Item is currency item... checking stash for %d %s.\n", g_Robot->AutoTrade->OurQuantity, g_Robot->AutoTrade->OurItemName.c_str());

		g_Robot->CurrencyInv->Items = g_Robot->CurrencyInv->GetInventoryItems();

		for each(Item* i in g_Robot->CurrencyInv->Items)
		{
			if (iequals(i->BaseName, g_Robot->AutoTrade->OurItemName))
			{
				stashContainsItem = CurrencyStashToInventory(i->BaseName, g_Robot->AutoTrade->OurQuantity, 1, 1);//take out from stash?

				Price = wstring(i->PriceTag);

				if (stashContainsItem)
				{			
					isRequestedItemNameABaseName = true;
				
					Sleep(2000);

					//need to check again...
					g_Robot->NormalInv->Items = g_Robot->NormalInv->GetInventoryItems(); //inventory, not stash!
		
					for each(Item* j in g_Robot->NormalInv->Items)
					{
						if (j->BaseName.size() > 0)
						{
							if (iequals(j->BaseName, g_Robot->AutoTrade->OurItemName))
							{						
								inventoryContainsItem = true;
								requestedElementIndex = j->InventoryEntityId;
								usingItemFullName = true;
								wprintf(L"[TRADE BOT] Found requested item in inventory list (full name: %s)\n", j->FullName.c_str());
							}
						}
					}

				}
			}
		}
	}
	else //NOT using currency -> dont use base name
	{
		g_Robot->NormalInv->Items = g_Robot->NormalInv->GetInventoryItems(); //inventory, not stash! 

		for each(Item* i in g_Robot->NormalInv->Items)
		{
			if (i->FullName.size() > 0)
			{
				if (iequals(i->FullName, g_Robot->AutoTrade->OurItemName))
				{
					isRequestedItemNameABaseName = false;
					inventoryContainsItem = true;
					requestedElementIndex = i->InventoryEntityId;
					usingItemFullName = true;
					wprintf(L"[TRADE BOT] Found requested item in inventory list (full name: %s)\n", i->FullName.c_str());
					break;
				}
			}
		}
	}

	if (!inventoryContainsItem)
	{
		printf("Item not in inventory, checking stash...\n");

		for (int i = 0; i < 4; i++) //get the first 4 tabs, tabs 5 and 6 will be trade boxes
		{
			g_Robot->StashInv[i]->ForceLoadTab(i); //no need to force load if already interacting
			Sleep(1000);

			if (!IsCurrencyItem(g_Robot->AutoTrade->OurItemName))
				stashContainsItem = StashToInventory(g_Robot->AutoTrade->OurItemName, i, false); //sketchy function, check the false...
			else
				stashContainsItem = StashToInventory(g_Robot->AutoTrade->OurItemName, i, true); //sketchy function, check the false...
		}
		
		if (stashContainsItem)
		{
			printf("Found requested item in stash.. proceeding.\n");
			inventoryContainsItem = true;
		}
		else
		{
			printf("Could not find required item in stash! Halting...\n");
			g_Robot->AutoTrade->IsInTrade = false;
			return;
		}
	}

	Sleep(2000);

	if (inventoryContainsItem)
	{
		wprintf(L"Partying %s...\n", g_Robot->AutoTrade->TradingPlayerName.c_str());

		//invite other player
		PacketWriter* p = PacketBuilder::InviteToParty((wchar_t*)g_Robot->AutoTrade->TradingPlayerName.c_str());
		PacketBuilder::Send(p);
	}
	else
	{
		printf("No items found in stash or inventory. Exiting.\n");
		g_Robot->AutoTrade->IsInTrade = false;
		return;
	}

	
	//wait for player to join room... use waitsingleobject
	g_Robot->AutoTrade->PlayerWaitThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)WaitForPlayer, 0, 0, 0);

	if (WaitForSingleObject(g_Robot->AutoTrade->PlayerWaitThread, 20000) == WAIT_TIMEOUT) //wait 10 seconds or else forget them and move on
	{
		printf("Player took more than 20 seconds/is not present. Waiting for next trade...\n");
		g_Robot->AutoTrade->IsInTrade = false;

		PacketWriter* p2 = PacketBuilder::CancelPartyInvite((wchar_t*)g_Robot->AutoTrade->TradingPlayerName.c_str()); //better would be to check some way if in party first..
		PacketBuilder::Send(p2);

		return;
	}
	
	Sleep(5000);

	//get other player id
	if (g_Robot->AutoTrade->InteractingPlayer != NULL)
	{
		PacketWriter* tp = PacketBuilder::TradePlayer(g_Robot->AutoTrade->InteractingPlayer->GetUniqueID()); //trade other player
		PacketBuilder::Send(tp);
		delete tp;
	}
	
	Sleep(10000);

	PacketWriter* tp = PacketBuilder::PlaceItemInSellWindow(requestedElementIndex, 1, 1);
	PacketBuilder::Send(tp);
		
	Sleep(5000);

	bool windowHasItem = false;

	g_Robot->AutoTrade->TaskThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&WaitForWindowItem, 0, 0, 0);
	
	if (WaitForSingleObject(g_Robot->AutoTrade->TaskThread, 20000) == WAIT_TIMEOUT) //wait 20 seconds or else forget them and move on
	{
		printf("Player took more than 20 seconds to put item in window, exiting...\n");
		g_Robot->AutoTrade->IsInTrade = false; //todo make function to un-init
		TerminateThread(g_Robot->AutoTrade->TaskThread, 0);

		PacketWriter* p2 = PacketBuilder::CancelPartyInvite((wchar_t*)g_Robot->AutoTrade->TradingPlayerName.c_str()); //kick player
		PacketBuilder::Send(p2);
		return;
	}

	if (!DoTradeWindowItemsMeetPrice(Price))
	{
		wprintf(L"Items in trade don't match buyout price listed: %s\n", Price.c_str());
		g_Robot->AutoTrade->IsInTrade = false;
		PacketWriter* p2 = PacketBuilder::CancelPartyInvite((wchar_t*)g_Robot->AutoTrade->TradingPlayerName.c_str()); //kick player
		PacketBuilder::Send(p2);
		return;
	}

	printf("Found item in trade window, proceeding..\n");
	
	Sleep(2000);

	//accept trade
	PacketWriter* p1 = PacketBuilder::AcceptTrade(2); //this number is something like total items in windows combined?? wtf
	PacketBuilder::Send(p1);
	
	printf("Accepted trade!\n");
	Sleep(2000);

	//kick player
	PacketWriter* p2 = PacketBuilder::CancelPartyInvite((wchar_t*)g_Robot->AutoTrade->TradingPlayerName.c_str());
	PacketBuilder::Send(p2);

	Sleep(2000);

	//wstring msg = L"/local ty!";
	//PacketWriter* p3 = PacketBuilder::PlayerMessage((wchar_t*)msg.c_str());
	//PacketBuilder::Send(p3);
	
	//Sleep(2000);


	g_Robot->NormalInv->Items = g_Robot->NormalInv->GetInventoryItems(); //inventory, not stash!
	
	int StashItemIndex = 0;

	for each(Item* j in g_Robot->NormalInv->Items)
	{
		if (j->BaseName.size() > 0)
		{
			if (iequals(j->BaseName, g_Robot->AutoTrade->OurItemName))
			{
				inventoryContainsItem = true;
				StashItemIndex = j->InventoryEntityId;
				usingItemFullName = true;
				wprintf(L"[TRADE BOT] Found requested item in inventory list (full name: %s)\n", j->FullName.c_str());

			}
		}
		else if (j->FullName.size() > 0)
		{
			if (iequals(j->BaseName, g_Robot->AutoTrade->OurItemName))
			{
				inventoryContainsItem = true;
				StashItemIndex = j->InventoryEntityId;
				usingItemFullName = true;
				wprintf(L"[TRADE BOT] Found requested item in inventory list (full name: %s)\n", j->FullName.c_str());

			}
		}
	}

	//interact with stash npc

	//stash items
	g_Robot->Interaction(stash->GetUniqueID(), 0x0266);

	Sleep(2000);

	if (IsCurrencyItem(g_Robot->AutoTrade->TheirItemName))
	{
		InventoryToStash(g_Robot->AutoTrade->TheirItemName, 4, true); //4 is our currency tab. . . this wont work for non-currency items
	}
	else
	{
		InventoryToStash(g_Robot->AutoTrade->TheirItemName, 1, false); //TODO: find dynamic way to put into stash without full tab
	}

	FileIO::WriteColorTextConsole("[AUTO TRADE] Trade Cycle complete.\n", FOREGROUND_GREEN);
	
	g_Robot->AutoTrade->IsInTrade = false;

	delete p1, p2, tp;
}

void WaitForPlayer()
{
	bool found = false;

	while (!found)
	{
		if (g_Robot->AutoTrade->InteractingPlayer == NULL)
		{
			Sleep(2000);
		}
		else
		{
			found = true;
		}
	}
}


void WaitForWindowItem()
{
	bool found = false;

	while (!found)
	{
		found = g_Robot->TradeWindowRemote->ContainsItem(Inventory::TradeWindowSide::Remote, g_Robot->AutoTrade->TheirItemName, g_Robot->AutoTrade->TheirItemQuantity, true);
		wprintf(L"Waiting for item to be in trade window: %s, %d...\n", g_Robot->AutoTrade->TheirItemName.c_str(), g_Robot->AutoTrade->TheirItemQuantity);
		Sleep(2000);
	}	
}

BOOL CurrencyStashToInventory(std::wstring itemBaseName, int StackSize, int PlaceInX, int PlaceInY)
{
	if (g_Robot->CurrencyInv->Items.size() == 0)
		return FALSE;

	for each (Item* i in g_Robot->CurrencyInv->Items) //need this for other pages not just first
	{
		if (iequals(itemBaseName, i->BaseName))
		{ 
			if (i->stackSize >= StackSize)
			{
				wprintf(L"Withdrawing item: %s\n", itemBaseName.c_str());

				PacketWriter* p = PacketBuilder::CreateItemStack(0x49, i->InventoryEntityId, StackSize);
				UINT64 SendClass = GetSendClass();

				if (SendClass != NULL)
					SendPacket(SendClass, (LPBYTE)p->GetBuffer(), p->GetSize());

				delete p;

				//item is now on mouse...
				PacketWriter* p1 = PacketBuilder::MoveInventoryItem(PlaceInX, PlaceInY);

				SendClass = GetSendClass();

				if (SendClass != NULL)
					SendPacket(SendClass, (LPBYTE)p1->GetBuffer(), p1->GetSize());

				delete p1;

				return TRUE;
			}
			else
			{
				printf("Stack not large enough, continuing...\n");
			}
		}
	}

	printf("Could not find item in stash!\n");
	return FALSE;

}

//change this from entity name to unique name??
BOOL StashToInventory(std::wstring EntityName, int tab, bool isCurrencyTab) //change this away from [0], add tab param
{
	if (g_Robot->StashInv[tab]->Items.size() == 0)
		return FALSE;

	for each (Item* i in g_Robot->StashInv[tab]->Items) //need this for other pages not just first
	{
		if (isCurrencyTab)
		{
			if (iequals(EntityName, i->BaseName)) //found entity... withdraw it to inv then read inv?
			{
				PacketWriter* p = PacketBuilder::WindowToInventory(i->InventoryEntityId, 4);
				PacketBuilder::Send(p);
				delete p;

				return TRUE;
			}
		}
		else
		{
			if (iequals(EntityName, i->FullName)) //found entity... withdraw it to inv then read inv?
			{
				PacketWriter* p = PacketBuilder::WindowToInventory(i->InventoryEntityId, 5);
				PacketBuilder::Send(p);
				delete p;

				return TRUE;
			}
		}

	}

	return FALSE;
}

wstring PriceNameToItemName(wstring priceTagName) //finish this
{
	wstring realName;
	
	if (iequals(priceTagName, L"chaos"))
	{
		realName = wstring(L"Chaos Orb");
	}
	else if (iequals(priceTagName, L"exalted"))
	{
		realName = wstring(L"Exalted Orb");
	}
	else if (iequals(priceTagName, L"alchemy"))
	{
		realName = wstring(L"Orb of Alchemy");
	}
	else if (iequals(priceTagName, L"vaal"))
	{
		realName = wstring(L"Vaal Orb");
	}
	else if (iequals(priceTagName, L"offer-dedication"))
	{
		realName = wstring(L"Dedication To The Goddess");
	}
	else if (iequals(priceTagName, L"awakened-sextant"))
	{
		realName = wstring(L"Awakened Sextant");
	}
	else if (iequals(priceTagName, L"simple-sextant"))
	{
		realName = wstring(L"Simple Sextant");
	}
	else if (iequals(priceTagName, L"prime-sextant"))
	{
		realName = wstring(L"Prime Sextant");
	}
	else if (iequals(priceTagName, L"facetors"))
	{
		realName = wstring(L"Facetor's Lens");
	}
	else if (iequals(priceTagName, L"whetstone"))
	{
		realName = wstring(L"Blacksmith's Whetstone");
	}
	else if (iequals(priceTagName, L"scrap"))
	{
		realName = wstring(L"Armourer's Scrap");
	}
	else if (iequals(priceTagName, L"chisel"))
	{
		realName = wstring(L"Cartographer's Chisel");
	}
	else if (iequals(priceTagName, L"mirror"))
	{
		realName = wstring(L"Mirror of Kalandra");
	}


	return realName;
}

BOOL DoTradeWindowItemsMeetPrice(wstring priceTag) //"~price %d %s"     
{
	if (priceTag.size() == 0)
		return false;

	wprintf(L"%s\n", priceTag.c_str());

	wchar_t* trimmed = std::wcstok((wchar_t*)priceTag.c_str(), L" ");

	int quantity = 0;
	wstring itemName;

	while (trimmed != NULL)
	{
		if (trimmed[0] >= L'0' && trimmed[0] <= L'9')
		{
			quantity = _wtoi(trimmed); 
		}
		else if (trimmed[0] == L'~') //skip
		{

		}
		else
		{
			if (itemName.size() > 0)
			{
				itemName = itemName + L" " + wstring(trimmed);
			}
			else
				itemName = trimmed;

		}

		trimmed = wcstok(NULL, L" ");
	}

	if (quantity == 0)
	{
		printf("Failed to parse price tag. \n");
		return false;
	}

	wstring realName = PriceNameToItemName(itemName);

	g_Robot->TradeWindowRemote->Items = g_Robot->TradeWindowRemote->GetTradeWindowItems(Inventory::TradeWindowSide::Remote, true);

	int quantityInWindow = 0;

	if (g_Robot->TradeWindowRemote->Items.size() > 0)
	{
		for each (Item* i in g_Robot->TradeWindowRemote->Items)
		{
			if (iequals(realName, i->BaseName)) //todo: make this friendly for not just base name
			{
				quantityInWindow = quantityInWindow + i->stackSize;
			}
		}
	}
	else
	{
		printf("g_Robot->TradeWindowRemote->Items.size was 0!\n");
		return false;
	}

	if (quantityInWindow >= quantity)
		return true;
	else
		return false;
}

BOOL InventoryToStash(std::wstring EntityName, int tab, bool hasAffinity) // todo: add affinities for easy stashing
{
	if (g_Robot->NormalInv->Items.size() == 0)
		return FALSE;

	for each (Item* i in g_Robot->NormalInv->Items) //need this for other pages not just first
	{
		if (iequals(EntityName, i->FullName)) //found entity... withdraw it to inv then read inv?
		{
			if (hasAffinity)
			{
				PacketWriter* p = PacketBuilder::InventoryToAffinityStash(i->InventoryEntityId, tab);
				PacketBuilder::Send(p);
			}
			else
			{
				PacketWriter* p = PacketBuilder::InventoryToStash(i->InventoryEntityId, tab);
				PacketBuilder::Send(p);
			}

			return TRUE;
		}
	}

	return FALSE;
}

void SearchItems(const char* server, const char* itemName, const char* buyoutCurrency, int buyoutMax) //todo: slowly add in all params lol
{
	ofstream file;
	file.open("new_search.txt");

	file << server << endl; //write our input file
	file << itemName << endl;
	file << "type=" << endl; 
	file << "base=" << endl;
	file << "dmg_min=" << endl;
	file << "dmg_max=" << endl;
	file << "aps_min=" << endl;
	file << "aps_max=" << endl;
	file << "crit_min=" << endl;
	file << "crit_max=" << endl;
	file << "dps_min=" << endl;
	file << "dps_max=" << endl;
	file << "edps_min=" << endl;
	file << "edps_max=" << endl;
	file << "pdps_min=" << endl;
	file << "pdps_max=" << endl;
	file << "armour_min =" << endl;
	file << "armour_max=" << endl;
	file << "evasion_min=" << endl;
	file << "evasion_max=" << endl;
	file << "shield_min=" << endl;
	file << "shield_max=" << endl;
	file << "block_min=" << endl;
	file << "block_max=" << endl;
	file << "sockets_min=" << endl;
	file << "sockets_max=" << endl;
	file << "link_min=" << endl;
	file << "link_max=" << endl;
	file << "sockets_r=" << endl;
	file << "sockets_g=" << endl;
	file << "sockets_b=" << endl;
	file << "sockets_w=" << endl;
	file << "linked_r=" << endl;
	file << "linked_g=" << endl;
	file << "linked_b=" << endl;
	file << "linked_w=" << endl;
	file << "rlevel_min=" << endl;
	file << "rlevel_max=" << endl;
	file << "rstr_min=" << endl;
	file << "rstr_max=" << endl;
	file << "rdex_min=" << endl;
	file << "rdex_max=" << endl;
	file << "rint_min=" << endl;
	file << "rint_max=" << endl;
	file << "mod_name=" << endl;
	file << "mod_min=" << endl;
	file << "mod_max=" << endl;
	file << "mod_weight=" << endl;
	file << "group_type=And" << endl; 
	file << "group_min=" << endl;
	file << "group_max=" << endl;
	file << "group_count=1" << endl;
	file << "q_min=" << endl;
	file << "q_max=" << endl;
	file << "level_min=" << endl;
	file << "level_max=" << endl;
	file << "ilvl_min=" << endl;
	file << "ilvl_max=" << endl;
	file << "rarity=" << endl;
	file << "progress_min=" << endl;
	file << "progress_max=" << endl;
	file << "sockets_a_min=" << endl;
	file << "sockets_a_max=" << endl;
	file << "map_series=" << endl;
	file << "altart=" << endl;
	file << "identified=" << endl;
	file << "corrupted=" << endl;
	file << "crafted=" << endl;
	file << "enchanted=" << endl;
	file << "fractured=" << endl;
	file << "synthesised=" << endl;
	file << "mirrored=" << endl;
	file << "veiled=" << endl;
	file << "shaper=" << endl;
	file << "elder=" << endl;
	file << "crusader=" << endl;
	file << "redeemer=" << endl;
	file << "hunter=" << endl;
	file << "warlord=" << endl;
	file << "replica=" << endl;
	file << "seller=" << endl;
	file << "thread=" << endl;
	file << "online=x" << endl;
	file << "capquality=x" << endl; 
	file << "buyout_min=" << endl;
	file << "buyout_max=" << buyoutMax << endl;
	file << "buyout_currency=" << buyoutCurrency << endl;
	file << "has_buyout=1" << endl; 
	file << "exact_currency=x" << endl; 

	file.close();

	//invoke 'ListingGrabber.exe new_search.txt'
	HINSTANCE hInst = ShellExecuteA(NULL, NULL, "ListingGrabber.exe", "new_search.txt", NULL, SW_SHOWMINIMIZED); //if this doesnt work/launch, check the path/hardcode it!!
	
	//read out.txt, put whispers or listings into a list, whisper each person in list
	if (hInst < (HINSTANCE)32)
	{
		FileIO::Log("Could not run ListingGrabber, please make sure all tools are present before botting.\n");
		return;
	}

}

void SearchCurrencyItems(const char* server, const char* itemNameHave, const char* itemNameWant, int buyoutMax)
{
	ofstream file;
	file.open("currency_search.txt");

	file << server << endl; //write our input file
	file << itemNameHave << endl;
	file << itemNameWant << endl;

	file.close();

	//invoke 'ListingGrabber.exe new_search.txt'
	HINSTANCE hInst = ShellExecuteA(NULL, NULL, "CurrencyListingGrabber.exe", "currency_search.txt", NULL, SW_SHOWMINIMIZED); //if this doesnt work/launch, check the path/hardcode it!!

	//read out.txt, put whispers or listings into a list, whisper each person in list
	if (hInst < (HINSTANCE)32)
	{
		FileIO::Log("Could not run ListingGrabber, please make sure all tools are present before botting.\n");
		return;
	}

}


