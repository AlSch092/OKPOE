#pragma once
#include <Windows.h>
#include <iostream>

using namespace std;

namespace OS
{
	string GetCurrentUsername();
	int GetCPUID();
	bool SetDebugPrivilege(bool Enable);
	bool IsElevated();
}