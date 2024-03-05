#include "AutoPlayer.hpp"

extern AutoPlayer* g_Robot;
extern NetLogger* g_ProtectionServer;

AutoPlayer::AutoPlayer()
{
	this->InputQueue = new std::queue<Input::Inputs*>();

	this->GameHelper = new TaskHelper();

	this->haReduceRAM = NULL;
	this->InputThread = NULL;
	this->ScriptingThread = NULL;
	this->AutoChickenThread = NULL;
	this->FollowPlayerThread = NULL;
	this->MonsterHuntingThread = NULL;

	//this->LocalPlayer = GetLocalPlayer(); //crashing line...

	this->NormalInv = new NormalInventory();
	this->CurrencyInv = new CurrencyInventory();

	for (int i = 0; i < TABS_LOGGED; i++) //default 4 tab pages... THIS CRASHES IF TABS_LOGGED IS WRONG...
	{
		this->StashInv[i] = new StashInventory();
	}
	
	this->TradeWindowRemote = new TradeInventory();
	this->TradeWindowLocal = new TradeInventory();

	this->AutoTrade = new Trade;
	this->AutoTrading = false;

	if (this->AutoTrade == NULL)
		printf("AutoTrade was NULL!\n");
	else
	{
		this->AutoTrade->IsInTrade = false;
	}

	this->InputQueue = new std::queue<Input::Inputs*>();

	this->GroundItemList = std::list<GroundItem*>();

	this->Attacker = new AutoAttacker();
	this->Attacker->IsAttacking = false;

	this->Flasker = new AutoFlask();
}

void AutoPlayer::HandleEntityLabelSpawn(UINT64 pObject, LPCWSTR swLabel) //seems to trigger for -all- PORTAL type labels, large and small.
{
	if (swLabel != nullptr)
	{
		if (wcslen(swLabel) > 0)
		{
			wprintf(L"Spawned label: %s\n", swLabel);
			
			bool isDuplicate = false;
			for each(wstring s in g_Robot->VisiblePortals) //th
			{
				if (wcscmp(s.c_str(), swLabel) == 0)
					isDuplicate = true;
			}

			if (!isDuplicate)
				g_Robot->VisiblePortals.push_back(wstring(swLabel));
		}
	}
}

void AutoPlayer::HandleEntitySpawn(UINT64 EntityAddr)
{
	if (EntityAddr == 0)
		return;

	Entity* Ent = new Entity(EntityAddr);

	if (Ent == NULL)
	{
		FileIO::Log("[ERROR] Could not allocate Entity at HandleEntitySpawn!\n");
		return;
	}

	//Begin decision making based on spawn
	if (wcscmp(Ent->FilePath, L"Metadata/MiscellaneousObjects/WorldItem") == 0)
	{	
		HandleItemDrop(Ent);
	}
	else if (wcsstr(Ent->FilePath, L"Metadata/Monsters/"))
	{
		HandleMonsterSpawn(Ent);
	}
	else if (wcscmp(Ent->FilePath, L"Metadata/MiscellaneousObjects/Stash") == 0)
	{
		g_Robot->StashID = Ent->GetUniqueID();
	}
	else if (wcsstr(Ent->FilePath, L"Metadata/Characters/"))
	{
		HandlePlayerControlled(Ent);
	}
	else if (wcsstr(Ent->FilePath, L"Chests/StrongBoxes"))
	{
		HandleStrongbox(Ent);
	}
	else if (wcsstr(Ent->FilePath, L"Objects/AreaTransition") != NULL || wcscmp(Ent->FilePath, L"Metadata/MiscellaneousObjects/MultiplexPortal") == 0)
	{
		HandleAreaTransition(Ent);
	}
	else if (wcscmp(Ent->FilePath, L"Metadata/MiscellaneousObjects/Waypoint") == 0)
	{
		printf("Waypoint detected!\n");
		g_Robot->WaypointId = Ent->GetUniqueID();
	}

	bool duplicate = false;

	uint32_t id = Ent->GetUniqueID();

	for each(Entity* e in g_Robot->EntityList) //add entity to our cache if it;s not already in it
	{
		if (e->GetUniqueID() == id)
		{
			duplicate = true;
		}
	}

	if (!duplicate) 
	{
		if (Ent->ComponentCount > 0)
			g_Robot->EntityList.push_back(Ent); //needs memory cleaning after being used..
	}
}

void AutoPlayer::HandleStrongbox(Entity* e)
{
	if (!Chest::IsOpened(e) && !Chest::IsLocked(e)) // ??
	{
		FileIO::Log("[INFO] Found unopened Strongbox!\n");	
			
		bool duplicate = false;

		for each(Entity* et in g_Robot->StrongboxList)
		{
			if (et->GetUniqueID() == e->GetUniqueID())
			{
				duplicate = true;
			}
		}

		if (!duplicate)
		{
			printf("Added box to list...\n");
			g_Robot->StrongboxList.push_back(new Entity(e->Address-8));
		}

		if (wcsstr(e->FilePath, L"StrongboxDivination") != NULL)
			FileIO::WriteColorTextConsole("Divination Strongbox detected!", BACKGROUND_GREEN);
		
		else if (wcsstr(e->FilePath, L"Arcanist") != NULL)
			FileIO::WriteColorTextConsole("Arcanist/Currency Strongbox detected!", BACKGROUND_GREEN | BACKGROUND_RED);
		
		else if (wcsstr(e->FilePath, L"Cartographer") != NULL)
			FileIO::WriteColorTextConsole("Cartographer's Strongbox detected!", BACKGROUND_BLUE);
		
		else if (wcsstr(e->FilePath, L"Scarab") != NULL)
			FileIO::WriteColorTextConsole("Operative's Strongbox detected!", BACKGROUND_RED);
		
		else if (wcsstr(e->FilePath, L"Armory") != NULL)
			printf("Armorer's Strongbox detected: %d\n", e->GetUniqueID());
		
		else if (wcsstr(e->FilePath, L"Arsenal") != NULL)
			printf("Blacksmith's/Weapons Strongbox detected: %d\n", e->GetUniqueID());
		
		else if (wcsstr(e->FilePath, L"Jeweller") != NULL)
			printf("Jewelery/Item Sockets Strongbox detected: %d\n", e->GetUniqueID());
		
		else if (wcsstr(e->FilePath, L"Artisan") != NULL)
			printf("Artisan's/Item Quality Strongbox detected: %d\n", e->GetUniqueID());
		
		else if (wcsstr(e->FilePath, L"Gemcutter") != NULL)
			printf("Gemcutter's Strongbox detected: %d\n", e->GetUniqueID());
		
		else if (wcsstr(e->FilePath, L"Large") != NULL)
			printf("Large Strongbox detected: %d\n", e->GetUniqueID());
		
	}
}

void AutoPlayer::HandleAreaTransition(Entity* e)
{
	Vector2 position = e->GetVector2();

	FileIO::Log("[INFO] Area Transition at position: %d,%d\n", position.X, position.Y);

	if (g_Robot->isAutoEnteringAreaTransition)
	{
		Entity* local = g_Robot->GetLocalPlayer();
		Vector2 playerPos = local->GetVector2();
		delete local;
		
		if (!Distances::IsPointInCircle(playerPos.X, playerPos.Y, position.X, position.Y, 150)) //stop from going back into new areas if spawned close to an area change
		{

		}
	}
}

void AutoPlayer::HandleMonsterSpawn(Entity* e)
{
	bool duplicate = false;

	int life = Life::GetEntityHP(e);

	if (life < 20 || life == -1 || Actor::GetCurrentActionID(e) == Actor::ACTION_DEAD || Positioned::IsFrozenOrDead(e)) //check if 0 hp or is a corpse (ACTION_DEAD)
		return;

	uint32_t id = e->GetUniqueID();

	for each (Entity*  e in g_Robot->MonsterList) //add entity to our cache if it;s not already in it
	{
		if (e->GetUniqueID() == id)	
			duplicate = true;	
	}

	if (!duplicate)
	{
		if (e->ComponentCount > 0)
			g_Robot->MonsterList.push_back(e); //needs memory cleaning after being used..
	}
}

void AutoPlayer::HandleOnAreaChange()
{
	g_Robot->FollowingUID = NULL;

	if (g_Robot->LocalPlayer != NULL)
	{
		delete g_Robot->LocalPlayer;
		g_Robot->LocalPlayer = NULL;
	}

	//for each(Actor::ActorSkill* A in g_Robot->Attacker->SkillsList)
	//{
	//	delete A; A = nullptr;
	//}

	g_Robot->Attacker->SkillsList.clear();

	g_Robot->VisiblePortals.clear();
	g_Robot->Attacker->SkillsList.clear();
	g_Robot->EntityList.clear();
	g_Robot->MonsterList.clear();
	g_Robot->StashID = 0;
	g_Robot->NPCID_Sales = 0;
}

void GetPlayerInfo(Entity* e)
{
	if (e->ComponentCount == 0)
		printf("Component count was 0!\n");

	wchar_t* name = Player::GetPlayerName(e);

	if (name != NULL)
	{
		wprintf(L"Player detected: %s\n", name);
		wprintf(L"Following: %s\n", g_Robot->FollowingPlayerName);

		if (wcscmp(name, g_Robot->FollowingPlayerName) == 0) //found autofollowing user... our thread should handle movement now after finding followingUid...
		{
			printf("Player name matches following name!\n");
			int uid = e->GetUniqueID();
			wprintf(L"[AUTO FOLLOW] Found name %s (%d).. starting input\n", name, uid);
			g_Robot->FollowingUID = uid;
			g_Robot->FollowingPlayer = e;
		}

	}
	else
	{
		printf("FollowingPlayerName was NULL!\n");
	}
}

void AutoPlayer::HandlePlayerControlled(Entity* e)
{
	if (e == NULL)
		return;

	int uid = e->GetUniqueID();
	bool duplicate = false;

	for each(Entity* e in g_Robot->PlayerList)
	{
		if (e->GetUniqueID() == uid)
		{
			duplicate = true;
		}
	}

	if (!duplicate)
		g_Robot->PlayerList.push_back(e);

	if (g_Robot->IsFollowingActor)
	{
		GetPlayerInfo(e);
	}
	else if (g_Robot->AutoTrading)
	{
		int uid = e->GetUniqueID();

		std::wstring name = Player::GetPlayerName(e);

		if (!g_Robot->AutoTrade->TradingPlayerName.empty())
		{
			if (name.compare(g_Robot->AutoTrade->TradingPlayerName) == 0)
			{
				wprintf(L"Found trading player entity: %s\n", name.c_str());

				if (g_Robot->AutoTrade->InteractingPlayer == NULL)
				{
					g_Robot->AutoTrade->InteractingPlayer = new Entity(e->Address - 8);
				}
			}
		}
	}
}

//raised spectres are no different than normal mobs in terms of component bases and such
//also for invincible monsters such as harbingers
bool AutoPlayer::IsMonsterIgnored(Entity* e)
{
	if (e == nullptr)
		return false;

	for each (wstring name in g_Robot->Attacker->IgnoredMonsters)
	{
		if(wcsstr(e->FilePath, name.c_str()) != NULL)
		{
			return true;
		}
	}

	return false;
}

void AutoPlayer::HandleItemDrop(Entity* e)
{
	if (e != NULL)
	{
		GroundItem* ParentItem = new GroundItem(e->Address - 8);

		GroundItem* SubItem = e->GetInnerItemEntity();
	
		if (SubItem != NULL)
		{
			wchar_t* filePath = SubItem->GetFilePathFromMemory();
			wprintf(L"[ITEM INFO] Worlditem: %s\n", filePath);

			int nSockets = Sockets::GetNumberOfSockets(SubItem);
			int nLinks = Sockets::GetSocketLinks(SubItem);

			//FileIO::Log("[ITEM INFO] Number of sockets in item: %d\n", nSockets);
			//FileIO::Log("[ITEM INFO] Links: %d\n", nLinks);
			//FileIO::Log("[ITEM INFO] Item level: %d\n", Mods::GetItemLevel(SubItem));
			//FileIO::Log("[ITEM INFO] Requires level: %d\n", Mods::GetRequiredLevel(SubItem));

			//if (nSockets == nLinks && nSockets >= 2)
			//{
			//	FileIO::Log("[ITEM INFO] Item has fully linked sockets.\n");
			//}

			//if (nSockets == 6)
			//{
			//	FileIO::Log("[ITEM INFO] Item has 6 sockets!\n");

			//	if (nLinks == 6)
			//	{
			//		FileIO::Log("[ITEM INFO] Item is fully linked and has 6 sockets! Loot recommended.\n");
			//		FileIO::Log("[ALERT] Item  with 6 links dropped!\n");
			//	}
			//}

			int nQuantity = Stack::GetStackSize(SubItem);
			if (nQuantity > 0)
			{
				printf("[ITEM INFO] Stack size: %d\n", nQuantity);
			}

			if (SubItem->GetComponentAddress("Base")) //not for public uploading!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			{
				wstring name = Base::GetBaseName(SubItem);

				if (!name.empty())
				{
					//		if (name == L"Gift to the Goddess")
					//		{
					//			Entity* local = g_Robot->GetLocalPlayer();
					//			if (local != NULL)
					//			{
					//				wstring charname = Player::GetPlayerName(local);
					//				char data[256] = { 0 };
					//				wcstombs(data, charname.c_str(), 50);
					//				strcat(data, " GttG:1");
					//				g_ProtectionServer->SendData(data);
					//				delete local; local = NULL;
					//			}	
					//		}
					//		else if (name == L"Dedication to the Goddess")
					//		{
					//			Entity* local = g_Robot->GetLocalPlayer();
					//			if (local != NULL)
					//			{
					//				wstring charname = Player::GetPlayerName(local);
					//				char data[256] = { 0 };
					//				wcstombs(data, charname.c_str(), 50);
					//				strcat(data, " DttG:1");
					//				g_ProtectionServer->SendData(data);
					//				delete local; local = NULL;
					//			}

					//		}
					//		else if (name == L"Tribute to the Goddess")
					//		{
					//			Entity* local = g_Robot->GetLocalPlayer();
					//			if (local != NULL)
					//			{
					//				wstring charname = Player::GetPlayerName(local);
					//				char data[256] = { 0 };
					//				wcstombs(data, charname.c_str(), 50);
					//				strcat(data, " TttG:1");
					//				g_ProtectionServer->SendData(data);
					//				delete local; local = NULL;
					//			}
					//		}

					if (!name.empty())
						SubItem->BaseName = wstring(name);
				}
			}

			if (SubItem->GetComponentAddress("Mods"))
			{
				std::wstring namePtr = Mods::GetUniqueName((Entity*)SubItem);

				if (!namePtr.empty())
				{
					SubItem->UniqueName = std::wstring(namePtr);
				}

				SubItem->ItemRarity = Mods::GetItemRarity(SubItem);

				switch (SubItem->ItemRarity)
				{
					case Mods::ItemRarities::Normal:
						wprintf(L"Normal item: %d\n", SubItem->ItemRarity);
						break;
					case Mods::ItemRarities::Magic:
						wprintf(L"Magic item: %d\n", SubItem->ItemRarity);
						break;
					case Mods::ItemRarities::Rare:
						wprintf(L"Rare item: %d\n", SubItem->ItemRarity);
						break;
					case Mods::ItemRarities::Unique:
						wprintf(L"Unique item: %d\n", SubItem->ItemRarity);
						break;
					case Mods::ItemRarities::Gem:
						wprintf(L"Gem item: %d\n", SubItem->ItemRarity);
						break;
					case Mods::ItemRarities::Prophecy:
						wprintf(L"Prophecy item: %d\n", SubItem->ItemRarity);
						break;
				}			
			}

			if (!SubItem->BaseName.empty())
			{
				if (!SubItem->UniqueName.empty())			
					SubItem->FullName = SubItem->UniqueName + L" " + SubItem->BaseName; //todo: change EntityName to Label or LabelName?			
				else
					SubItem->FullName = SubItem->BaseName;
						
				wprintf(L"SubItem Name: %s\n", SubItem->FullName.c_str());

				if (FileIO::FileHasLine(L"./loot.ini", SubItem->FullName.c_str())) //check if item is in our file
				{
					bool isDuplicate = false;

					for each (GroundItem * gi in g_Robot->GroundItemList)
					{
						if (gi->GetUniqueID() == SubItem->GetUniqueID())
						{
							isDuplicate = true;
							break;
						}
					}

					printf("Adding to SubItem list...\n");

					ParentItem->BaseName = wstring(SubItem->BaseName);
					ParentItem->UniqueName = wstring(SubItem->UniqueName);
					ParentItem->FullName = wstring(SubItem->FullName);

					if (!isDuplicate)
						g_Robot->GroundItemList.push_back(ParentItem);
				}
			}

			delete SubItem; SubItem = nullptr;
		}
		else
		{
			FileIO::Log("[AUTO LOOT] [WARNING!] Subobject was NULL at HandleItemDrop\n");
		}
	}
	else
	{
		FileIO::Log("[AUTO LOOT] [WARNING!] Object was NULL at HandleItemDrop\n");
	}

}

bool AutoPlayer::LootItems() //works well!
{
	bool removingElement = false;
	GroundItem* elementToRemove[30] = { nullptr }; //careful about using magic numbers as array sizes, a list would be safer
	int nRemoved = 0;

	if (!g_Robot->Attacker->IsBusy && !g_Robot->InTown && !g_Robot->Disconnected && !g_Robot->ChangingArea)
	{
		if (g_Robot->GroundItemList.size() > 0) //&& !Robot->NormalInv->isInventoryFull())
		{
			for each (GroundItem * e in g_Robot->GroundItemList)
			{
				g_Robot->IsLooting = true;

				if (e == nullptr)
					continue;

				if (e->GetComponentAddress("WorldItem") != 0 && (e->GetUniqueID() > 0 && e->GetUniqueID() < 0x5000000))
				{
					Entity* p = g_Robot->GetLocalPlayer();

					if (p == nullptr)
					{
						g_Robot->IsLooting = false;
						return false;
					}
						
					if (Distances::GetDistanceBetweenObjects(e->GetVector2(), p->GetVector2()) <= 200)
					{
						GroundItem* _Item = e->GetInnerItemEntity();

						if (_Item != NULL)
						{
							bool looping = true;

							std::wstring name = e->FullName;

							if (name.size() == 0)
							{
								printf("[ERROR] item name was NULL!\n");
								continue;
							}

							if (FileIO::FileHasLine(L"./loot.ini", name.c_str()))
							{
								if (Element::IsSubstringLabelOnScreen(name)) //working!
								{
									Vector2 GroundPos = Positioned::GetGroundPosition(e);

									if ((GroundPos.X != 0x7FFFFFFF && GroundPos.Y != 0x7FFFFFFF) && looping == true) //checks to make sure the item is on ground
									{
										GroundPos = Positioned::GetGroundPosition(e);

										if ((GroundPos.X == 0 && GroundPos.Y == 0))
										{
											elementToRemove[nRemoved] = e;
											nRemoved += 1;

											removingElement = true;
											printf("Removing item from list.\n");
											looping = false;
											continue;
										}

										wprintf(L"Looting item: %s (%d)!\n", name.c_str(), e->GetUniqueID());
										g_Robot->IsLooting = true;
										g_Robot->InteractIfInRange(e, 110);
										//g_Robot->Interaction(e->GetUniqueID(), 0x0266);
										Sleep(1500);
										g_Robot->IsLooting = false;
									}
								}
							}

							delete _Item; _Item = NULL;
						}
					}
				}		
			}

			for (int i = 0; i < nRemoved; i++)
			{
				g_Robot->GroundItemList.remove(elementToRemove[i]);
				delete elementToRemove[i]; elementToRemove[i] = nullptr;
			}
		}
	}
	else
	{
		printf("[AUTO-LOOT] Currently busy...\n");
		return false;
	}

	g_Robot->IsLooting = false; 
	return true;
}

void AutoPlayer::AutolootItems() //working mostly... gets unusable after crowded maps, is the list getting too big?
{
	printf("Started looting thread..\n");

	bool removingElement = false;
	GroundItem* elementToRemove[30] = { nullptr };
	int nRemoved = 0;

	while (g_Robot->AutoLooting)
	{
		if (!g_Robot->Attacker->IsBusy && !g_Robot->InTown && !g_Robot->Disconnected && !g_Robot->ChangingArea)
		{
				for each(GroundItem* e in g_Robot->GroundItemList) 
				{
					if (e == nullptr)
						continue;

					if (e->GetComponentAddress("WorldItem") != 0 && (e->GetUniqueID() > 0 && e->GetUniqueID() < 0x5000000))
					{
						GroundItem* _Item = e->GetInnerItemEntity();

						if (_Item != NULL)
						{
							bool looping = true;

							std::wstring name = e->FullName;

							if (name.size() == 0)
							{
								printf("[ERROR] item name was NULL!\n");
								delete _Item; _Item = nullptr;
								continue;
							}

							if (FileIO::FileHasLine(L"./loot.ini", name.c_str()))
							{
								if (Element::IsSubstringLabelOnScreen(name)) //working!
								{
									Vector2 GroundPos = Positioned::GetGroundPosition(e);
			
									if ((GroundPos.X != 0x7FFFFFFF && GroundPos.Y != 0x7FFFFFFF) && looping == true) //checks to make sure the item is on ground
									{
										GroundPos = Positioned::GetGroundPosition(e);

										if ((GroundPos.X == 0 && GroundPos.Y == 0))
										{
											elementToRemove[nRemoved] = e;
											nRemoved += 1;
											delete _Item; _Item = nullptr;
											removingElement = true;
											looping = false;
											continue;
										}

										wprintf(L"Looting item: %s (%d)!\n", name.c_str(), e->GetUniqueID());
										g_Robot->IsLooting = true;
										
										if (!g_Robot->InteractIfInRange(e, 110))
										{
											g_Robot->IsLooting = false;
											delete _Item; _Item = nullptr;
											continue;
										}

										Sleep(1000);
										g_Robot->IsLooting = false;
									}
								}
								//else
									//printf("[ERROR] Could not find item label on screen!\n");							
							}

							delete _Item; _Item = NULL;
						}
					}
					//else
						//printf("GetComponentAddress (WorldItem) Failed.\n");				
				}

				for (int i = 0; i < nRemoved; i++)
				{
					g_Robot->GroundItemList.remove(elementToRemove[i]);
					delete elementToRemove[i]; elementToRemove[i] = nullptr;
				}
		}
		else
		{
			printf("[AUTO-LOOT] Waiting to not be busy (town, etc)...\n");
			Sleep(7000); //if this sleep is too low we will crash when changing maps
		}
	}
}

void AutoPlayer::AutoOpenChests()
{
	printf("Started Chests + strongboxes opening thread...\n");

	while (g_Robot->isAutoOpeningChests)
	{
		if (g_Robot->EntityList.size() > 0)
		{
			for each(Entity* e in g_Robot->EntityList)
			{
				if (e->GetComponentAddress("Chest") > 0)
				{
					if (Targetable::IsTargetable(e))
					{
						if (!Chest::IsLocked(e) && !Chest::IsOpened(e))
						{
							Vector2 eV = e->GetVector2();
							Vector2 pV = g_Robot->GetLocalPlayer()->GetVector2();

							if (Distances::GetDistanceBetweenObjects(eV, pV) < 300)
							{
								printf("Attempting to open chest with Id: %d\n", e->GetUniqueID());
								PacketWriter* p = PacketBuilder::EntityInteraction(e->GetUniqueID(), 0x0266);
								PacketBuilder::Send(p);
								g_Robot->EndAction();
								Sleep(3000);
							}
						}
					}

					delete e;
				}

			}
		}
	}
}

Entity* AutoPlayer::GetLocalPlayer() 
{
	if (g_Robot->DebugMode)
	{
		printf("Called GetLocalPlayer\n");
	}

	UINT64 PoEBase = (UINT64)GetModuleHandleA("PathOfExile.exe");
	UINT64 ptrIngameState = PoEBase + g_ProtectionServer->Offsets[5];
	
	UINT64 Ptr = ReadPointer<UINT64>(ptrIngameState, Offsets::Pointers::LocalEntityOfs1);

	if (Ptr == NULL)
	{
		printf("GetLocalPlayer ptr was NULL: %llX\n", Ptr);
		return NULL;
	}

	Ptr += Offsets::Pointers::LocalEntityOfs2; //we get this from mov rcx,[rcx+X] inside char action func
	if (Ptr != NULL)
	{
		Ptr = DereferenceSafe<UINT64>(Ptr);
		if (Ptr != NULL)
			Ptr += Offsets::Pointers::LocalEntityOfs3;

		Ptr = DereferenceSafe<UINT64>(Ptr);
	}
	else
		return NULL;


	if (Ptr != NULL)
	{
		Entity* e = new Entity(Ptr);
		if (e != nullptr)
			return e;
	}	
	else
	{
		printf("GetLocalPlayer was null!\n");
	}

	return NULL;
}

//void AutoPlayer::Action(UINT16 SkillId, DWORD SelectedEntityID, Vector2* AtPosition)
//{
//	UINT64 Base = (UINT64)GetModuleHandleA(NULL);
//
//	UINT64 Address = Base + g_ProtectionServer->Offsets[9];
//	UINT64 Ptr = ReadPointer<UINT64>(Address, Offsets::LocalEntityOfs1);
//
//	if (Ptr != -1)
//	{
//		if ((UINT64)(Base + g_ProtectionServer->Offsets[4]) > Base)
//		{
//			ActionFunction AF = (ActionFunction)(Base + g_ProtectionServer->Offsets[4]);
//			if (SkillId == Input::InputIds::INTERACTION)
//				(*AF)(Ptr, SkillId, SelectedEntityID, 0);
//			else
//				(*AF)(Ptr, SkillId, 0, AtPosition); 
//		}
//	}
//}

void AutoPlayer::EndAction()
{
	PacketWriter* p = PacketBuilder::EndAction();
	UINT64 SendClass = GetSendClass();
	if (SendClass != NULL)
		PacketBuilder::Send(p);
}

void AutoPlayer::BeginAutoFollow()
{
	if (this->FollowPlayerThread == NULL)
	{
		FileIO::Log("[AUTO FOLLOW] Beginning Autofollow...\n");
		DWORD ThreadID;
		this->FollowPlayerThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)this->FollowPlayer, 0, 0, &ThreadID);
	}	
}

void AutoPlayer::FollowPlayer()
{
	FileIO::Log("[AUTO FOLLOW] FollowPlayer...\n");

	while (g_Robot->IsFollowingActor)
	{
		if (!g_Robot->Attacker->IsBusy && !g_Robot->Disconnected)
		{
			if (g_Robot->FollowingUID > 0) //if the uid > 0, we can try to move to it?
			{
				if (g_Robot->FollowingPlayer != NULL)
				{
					Entity* local = g_Robot->GetLocalPlayer();
					if (Actor::GetCurrentActionID(local) == Actor::ActionIDs::ACTION_NONE)
					{
						if (Targetable::IsTargetable(g_Robot->FollowingPlayer))//&& (Life::GetEntityHP(Robot->FollowingPlayer) > 0))
						{
							if (g_Robot->FollowPlayerSkill > 0)
							{
								FileIO::Log("[AUTO FOLLOW] Using interaction with: %u\n", g_Robot->FollowingUID);

								PacketWriter* p = PacketBuilder::EntityInteraction(g_Robot->FollowingUID, g_Robot->FollowPlayerSkill);

								PacketBuilder::Send(p);
								g_Robot->EndAction();

								Sleep(1000);
							}
							else
							{
								FileIO::Log("[AUTO FOLLOW] Using interaction with: %u\n", g_Robot->FollowingUID);

								PacketWriter* p = PacketBuilder::EntityInteraction(g_Robot->FollowingUID, Input::InputIds::RUN);
								PacketBuilder::Send(p);

								g_Robot->EndAction();

								Sleep(1000);
							}

						}
					}

					delete local;
				}
			}
			else
			{
				FileIO::Log("[AUTO FOLLOW] Entity ID was 0, please re-enter map or have them enter this area.\n");
			}

			Sleep(2000);
		}			
		else
		{
			printf("[AUTO FOLLOW] Bot is busy!\n");
			Sleep(3000);
		}
	}
}

bool AutoPlayer::IsCharacterStuck()
{
	Entity* local = g_Robot->GetLocalPlayer();
	Vector2 BeforePos = local->GetVector2();
	delete local; local = NULL;

	//move player
	Vector2 MoveToPos = { 0, 45 };
	PacketWriter* p = PacketBuilder::Action(Input::InputIds::RUN, NULL, MoveToPos.X, MoveToPos.Y);
	UINT64 SendClass = GetSendClass();
	if (SendClass != NULL)
	{
		PacketHelper::Send(SendClass, (LPBYTE)p->GetBuffer(), p->GetSize());
		g_Robot->EndAction();
	}
	else
		return false;

	//check char action id
	Entity* local1 = g_Robot->GetLocalPlayer();
	Vector2 AfterPos = local1->GetVector2();
	delete local1; local1 = NULL;

	if (AfterPos.X == MoveToPos.X && AfterPos.Y == MoveToPos.Y)
	{
		return true;
	}


	return false;
}

bool AutoPlayer::IsEntityInList(wstring wc)
{
	for each(auto& e in g_Robot->EntityList)
	{
		if (wcscmp(e->FilePath, wc.c_str()) == 0)
		{
			return true;
		}
	}

	return false;
}

void AutoPlayer::Interaction(uint32_t entityId, uint16_t actionId)
{
	if (g_Robot->Disconnected || g_Robot->Attacker->IsBusy)
		return;

	while (this->IsMoving)
		Sleep(100);

	Entity* local = g_Robot->GetLocalPlayer();

	if (local == NULL)
	{
		printf("[ERROR] GetLocalPlayer was NULL at Interaction!\n");
		return;
	}

	while (Actor::GetCurrentActionID(local) != 0)
		Sleep(100);

	delete local;

	this->IsMoving = true;

	PacketWriter* p = PacketBuilder::EntityInteraction(entityId, actionId);
	PacketBuilder::Send(p);
	EndAction();
	this->IsMoving = false;
}

bool AutoPlayer::StashItems()
{
	bool FoundLine = false;
	bool stashTabHasAffinity = true;

	std::wifstream infile("./stash.ini");
	std::wstring line;

	if (infile.bad())
	{
		printf("[ERROR] Couldn't read stash.ini! Please make sure it's in the PoE folder.\n");
		return false;
	}

	if (this->itemsToStash.size() > 0)
		this->itemsToStash.clear();

	int count = 0;

	while (std::getline(infile, line)) //make this more portable
	{
		if (line[0] == L'/' && line[1] == L'/') //dangerous? if empty indexes might crash
			continue;
		else
		{
			this->itemsToStash.push_back(wstring(line));
			count++;

			wprintf(L"%s\n", line.c_str());
		}	
	}

	infile.close();

	if (count == 0)
	{
		printf("No lines found in stash.ini or some other problem.. aborting stashing.\n");
		return false;
	}

	if (this->StashID > 0)
	{
		//read file, then compare inventory to list
		Interaction(this->StashID, Input::InputIds::INTERACTION);
		Sleep(6000);

		//inv + stash should be open now
		this->NormalInv->Items = this->NormalInv->GetInventoryItems(); //inventory, not stash!

		int tab = 5; //todo: make way to check if a tab is full or not, same as inventory one. need to read inventory structures for affinity

		if (this->NormalInv->Items.size() > 0)
		{
			for each(Item* i in this->NormalInv->Items)
			{
				for each(wstring w in this->itemsToStash)
				{
					if (w == i->FullName)
					{
						BOOL success = InventoryToStash(w, tab, stashTabHasAffinity);

						if (success)
						{
							wprintf(L"Stashed item: %s\n", w.c_str());
							Sleep(300);
						}
					}
				}
			}
		}
	}
	else
	{
		printf("[OKPOE LOG] stashID was 0!\n");
		return false;
	}

	return true;
}

bool AutoPlayer::SellItemsToNPC()
{
	bool FoundLine = false;

	std::wifstream infile("./sell.ini");
	std::wstring line;

	if (infile.bad())
	{
		printf("[ERROR] Couldn't read sell.ini! Please make sure it's in the PoE folder.\n");
		return false;
	}

	this->itemsToSell.clear();

	while (std::getline(infile, line)) //make this more portable
	{
		if (wcslen(line.c_str()) > 0)
		{
			this->itemsToSell.push_back(line);
		}
	}

	infile.close();

	//interact with the stash firstly
	for each(Entity* e in EntityList)
	{
		if (wcscmp(e->GetFilePathFromMemory(), L"Metadata/NPC/") == 0) //finish this
		{
			this->StashID = e->GetUniqueID();
		}
	}

	if (this->StashID > 0)
	{
		//read file, then compare inventory to list
		Interaction(this->StashID, Input::InputIds::INTERACTION);
		Sleep(6000);


		//inv + stash should be open now
		this->NormalInv->Items = this->NormalInv->GetInventoryItems(); //inventory, not stash!

		int tab = 0; //todo: make way to check if a tab is full or not, same as inventory one.

		if (this->NormalInv->Items.size() > 0)
		{
			for each(Item* i in this->NormalInv->Items)
			{
				for each(wstring w in this->itemsToStash)
				{
					if (w == i->FullName)
					{
						BOOL success = InventoryToStash(w, tab, false);

						if (success)
						{
							wprintf(L"Stashed item: %s\n", w.c_str());
							Sleep(1000);
						}

					}
				}
			}
		}
	}

	return true;
}

void AutoPlayer::ExitNPCDialog()
{
	PacketWriter* p = PacketBuilder::ExitNPCDialog();
	PacketBuilder::Send(p);
}

void AutoPlayer::PlayBackMovements()
{
	std::list<string> Vectors = FileIO::GetAllLines("Movement.txt");

	if (Vectors.size() > 0)
	{
		for each(string Vector in Vectors)
		{
			UINT32 X, Y;
			int result = sscanf(Vector.c_str(), "%d, %d\r\n", &X, &Y);

			if (result == 2) //found 2 coordinates
			{
				Entity* local = g_Robot->GetLocalPlayer();
				while (Actor::GetCurrentActionID(local) != 0)
					Sleep(100);

				delete local; local = NULL;

				PacketWriter* p = PacketBuilder::Action(Input::InputIds::RUN, 0, X, Y);
				PacketBuilder::Send(p);
				PacketWriter* p1 = PacketBuilder::EndAction();
				PacketBuilder::Send(p1);
				Sleep(200);
			}
		}
	}

	printf("Finished playing back movements.\n");
}

bool AutoPlayer::SpawnMap(uint16_t modifier, byte hero, byte endOption)
{
	PacketWriter* p = PacketBuilder::SpawnAtlasInstance(modifier, hero, endOption);
	return PacketBuilder::Send(p);
}

void AutoPlayer::RevealMap()
{
	Sleep(3000);

	UINT64 PointerBase = ((UINT64)GetModuleHandleA("PathOfExile.exe") + g_ProtectionServer->Offsets[1]);

	if (PointerBase != NULL)
	{
		UINT64 PointerTwo = *(UINT64*)PointerBase + Offsets::Pointers::MaphackPtrOfs1;
		if (PointerTwo != NULL)
		{
			UINT64 PointerThree = *(UINT64*)PointerTwo + Offsets::Pointers::RevealMap;

			if (PointerThree != NULL)
			{
				WritePointer<UINT16>(PointerTwo, Offsets::Pointers::RevealMap, 1);
				Sleep(100);
				WritePointer<UINT16>(PointerTwo, Offsets::Pointers::RevealMap, 0);
			}
		}
	}
}

bool AutoPlayer::InteractIfInRange(Entity* e, int distanceMax)
{
	auto local = g_Robot->GetLocalPlayer();
	auto v1 = e->GetVector2();
	auto pV = local->GetVector2();
	delete local; local = NULL;

	int DistanceAway = Distances::GetDistanceBetweenObjects(v1, pV);
	e->DistanceAwayFromLocalPlayer = DistanceAway;

	if (DistanceAway <= distanceMax)
	{
		g_Robot->Interaction(e->GetUniqueID(), Input::InputIds::INTERACTION);
		return true;
	}

	return false;
}

void AutoPlayer::Revive()
{
	g_Robot->Attacker->IsBusy = true;
	g_Robot->Attacker->HadDied = true;

	Sleep(2000); //to fix glitch where life shows above 0/lags behind 

	Entity* player = g_Robot->GetLocalPlayer();

	if (player == NULL)
		return;

	int life = Life::GetEntityHP(player);
	delete player;

	while (g_Robot->AutoReviving && life == -1)
	{
		player = g_Robot->GetLocalPlayer();

		if (player == NULL)
			return;

		printf("Reviving character...\n");

		if (g_Robot->ReviveInSameMap)
		{
			PacketWriter* p = PacketBuilder::Revive(false);
			PacketBuilder::Send(p);
			break;
		}
		else
		{
			PacketWriter* p = PacketBuilder::Revive(true);
			PacketBuilder::Send(p);
			break;
		}

		g_Robot->Attacker->IsBusy = false;

		Sleep(1000);
		life = Life::GetEntityHP(player);
		delete player;
	}
}