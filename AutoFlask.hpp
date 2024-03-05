#pragma once
#include "Packets.hpp"
#include "AutoPlayer.hpp"
#include "Inventory.hpp"

struct Item;

class AutoFlask
{
public:
	HANDLE FlaskerThread;
	static void AutoFlasker(LPVOID param);

	void SetHPMP(UINT HP, UINT MP) { this->FlaskOnHP = HP; this->FlaskOnMana = MP; }

private:
	
	void UseFlask(int index);
	void FillFlaskList();

	std::list<Item*> Flasks;

	Item* HealthFlask;
	Item* ManaFlask;
	Item* SpeedFlask; //the essentials

	bool isFlasking = false;

	UINT FlaskOnHP;
	UINT FlaskOnMana;
};