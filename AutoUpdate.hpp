#pragma once
#include <Windows.h>
#include <cstdio>
#include <string>

#pragma comment(lib, "Urlmon.lib")

using namespace std;

namespace AutoUpdate
{
	int CheckForUpdates(std::string currentVer);
	bool DownloadFile();
}
