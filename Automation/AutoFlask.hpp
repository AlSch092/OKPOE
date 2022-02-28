#pragma once
#include "Packets.hpp"
#include "AutoPlayer.hpp"
#include "Inventory.hpp"

struct Item;

class AutoFlask
{
public:

	static void AutoFlasker(LPVOID param);
	void BeginFlasker();

	void SetHPMP(UINT HP, UINT MP) { this->FlaskOnHP = HP; this->FlaskOnMana = MP; }
  HANDLE GetThreadWorker() { return this->FlaskerThread; }
  
private:
	
	void UseFlask(int index);
	void FillFlaskList();

	std::list<Item*> Flasks;

	Item* HealthFlask;
	Item* ManaFlask;
	Item* SpeedFlask; //the essentials

	bool isFlasking = false;

	HANDLE FlaskerThread;
	UINT FlaskOnHP;
	UINT FlaskOnMana;
};
