#pragma once
#define TABS_LOGGED 255
#include "Inventory.hpp"
#include "Packets.hpp"
#include "FileIO.hpp"

enum TradeDirection
{
	Sell,
	Buy
};

struct Listing
{
	string server;
	string ourItemNameUnique;
	int ourItemQuantity;
	string theirItem;
	string theirItemUnique;
	int theirItemQuantity;
	string PlayerName;
	bool Completed;
};

struct Exchange
{
	Listing* TradeInfo;
	TradeDirection ExchangeType;
};

struct Trade
{
	bool IsInTrade;
	bool UsingCurrencyMarket;

	HANDLE TaskThread = NULL;
	HANDLE PlayerWaitThread = NULL;

	string server;
	bool IsBuying;
	bool IsSelling;

	wstring OurItemName;
	int OurQuantity;

	wstring TheirItemName;
	int TheirItemQuantity;

	std::wstring TradingPlayerName;

	Entity* InteractingPlayer = NULL;

};


class AutoSeller
{
private:

public:
	int* publicTabPages;
	int TotalStashTabs;

	int TradesCompleted;
	std::list<Trade*> Trades;
};


void SearchItems(const char* server, const char* itemName, const char* buyoutCurrency, int buyoutMax);
void SearchCurrencyItems(const char* server, const char* itemName, const char* buyoutCurrency, int buyoutMax);

void AutoBuy();	
void AutoSell();
bool IsCurrencyItem(wstring name);
void WaitForPlayer();
void WaitForWindowItem();

BOOL StashToInventory(std::wstring EntityName, int tab, bool isCurrencyTab);
BOOL InventoryToStash(std::wstring EntityName, int tab, bool isCurrencyTab);

bool iequals(const wstring& a, const wstring& b);
BOOL CurrencyStashToInventory(std::wstring BaseName, int StackSize, int PlaceInX, int PlaceInY);

BOOL DoTradeWindowItemsMeetPrice(wstring priceTag);
wstring PriceNameToItemName(wstring priceTagName);
