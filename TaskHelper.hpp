#pragma once
#include "AutoPlayer.hpp"

class AutoPlayer;

extern AutoPlayer* g_Robot;

class TaskHelper
{
public:

	bool ExchangeDivinationCards(AutoPlayer* g_Robot);
	uint32_t GetDivinationNPCID() { return this->DivinationExchangeNPCID; }
	void SetDivinationNPCID(uint32_t id) { this->DivinationExchangeNPCID = id; }

	void SelectNPCDialog(byte index);

	static void AutoClickSwitches(); //trial helper

	HANDLE GetThread() { return this->TaskThread; }

private:

	uint32_t DivinationExchangeNPCID = 0;
	HANDLE TaskThread = NULL;
};
