#include "FileIO.hpp"
#include <stdarg.h>
#include <codecvt>

extern AutoPlayer* g_Robot;
extern NetLogger* g_ProtectionServer;

bool FileIO::FileHasLine(wchar_t* FilePath, const wchar_t* Substring)
{
	bool FoundLine = false;

	std::wifstream infile(FilePath);
	std::wstring line;

	if (infile.bad())
	{
		printf("[ERROR] Couldn't read/find loot.ini! Please make sure it's in the PoE folder.\n");
		return false;
	}

	while (std::getline(infile, line)) //make this more portable
	{
		if (wcsstr(Substring, line.c_str()) != NULL)
		{
			FoundLine = true;
			infile.close();
			return FoundLine;
		}
	}

	infile.close();

	return FoundLine;
}

int FileIO::GetDesiredSocketsFromFile(wchar_t* FilePath, wchar_t* Substring)
{
	bool FoundLine = false;
	int Sockets = 0;

	std::wifstream infile(FilePath);
	std::wstring line;

	if (infile.bad())
	{
		printf("[ERROR] Couldn't read/find loot.ini! Please make sure it's in the PoE folder.\n");
		return false;
	}

	while (std::getline(infile, line)) //make this more portable
	{
		if (wcsstr(Substring, line.c_str()) != NULL)
		{
			FoundLine = true;

			std::wstringstream iss(line);
			std::wstring word;
			while (iss >> word) 
			{
				if (word.size() == 1)
				{
					Sockets = _wtoi(word.c_str());
					break;
				}
			}
		}
	}

	infile.close();

	return Sockets;
}

int FileIO::GetDesiredLinksFromFile(wchar_t* FilePath, wchar_t* Substring)
{
	bool FoundLine = false;
	int Sockets = 0;
	int count = 0;

	std::wifstream infile(FilePath);
	std::wstring line;

	if (infile.bad())
	{
		printf("[ERROR] Couldn't read/find loot.ini! Please make sure it's in the PoE folder.\n");
		return false;
	}

	while (std::getline(infile, line)) //make this more portable
	{
		if (wcsstr(Substring, line.c_str()) != NULL)
		{
			FoundLine = true;

			std::wstringstream iss(line);
			std::wstring word;
			while (iss >> word)
			{
				if (word.size() == 1 && count > 0)
				{
					Sockets = _wtoi(word.c_str());
					break;
				}

				count += 1;
			}
		}
	}

	infile.close();

	return Sockets;
}

void FileIO::WLog(const wchar_t* format, ...) {
	
	va_list args;
	wchar_t buffer[1024];

	va_start(args, format);
	vswprintf(buffer, format, args);
	va_end(args);

	wprintf(L"%s\n", buffer);
}

void FileIO::Log(const char* format, ...) {

	va_list args;
	char buffer[1024];

	va_start(args, format);
	vsprintf(buffer, format, args);
	va_end(args);

	printf("%s\n", buffer);
}

void FileIO::FileLog(const char* format, ...) {

	va_list args;
	char buffer[1024];

	va_start(args, format);
	vsprintf(buffer, format, args);
	va_end(args);

	std::fstream file;
	file.open("OK.log", std::ios_base::in | std::ios_base::app);
	file << buffer << '\r' << '\n';
	file.close();

}

void FileIO::ClientMessageHook(void* StackPtrUnk, int fileMode, char* msg, int msgSizeBytes)
{
	char nMsg[1024] = { 0 };

	if (msg == nullptr || msgSizeBytes == 0)
		return;

	for (int i = 0; i < msgSizeBytes; i++)
	{
		if (msg[i] == 0x0A)
			nMsg[i] = '\0';
		else
			nMsg[i] = msg[i];
	}

	printf("%s\n", nMsg);

	if (strstr(msg, "[SHADER] Delay: ON") != NULL)
	{
		FileIO::Log("[OKPOE LOG] Entered New Area.\n");
		g_Robot->Attacker->IsBusy = false;
		g_Robot->Disconnected = false;
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)g_Robot->RevealMap, 0, 0, 0);
	}
	else if (strstr(msg, "has committed suicide.") != NULL || strstr(msg, "has been slain.") != NULL)
	{
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)AutoPlayer::Revive, 0, 0, 0);
	}
	else if (strstr(msg, "Generating level") != NULL)
	{
		int areaLevel;
		int areaSeed;
		char areaName[150];

		g_Robot->ChangingArea = true;

		auto substr = strstr(msg, "Generating level");

		if (substr != NULL)
		{
			auto result = sscanf(substr, "Generating level %d area \"%s\" with seed %d", &areaLevel, areaName, &areaSeed);

			if (result)
			{
				if (areaName[strlen(areaName) - 1] == '"')
					areaName[strlen(areaName) - 1] = '\0';

				g_Robot->Attacker->IsBusy = true;

				g_Robot->NumberedAreaName = string(areaName);

				if (strstr(g_Robot->NumberedAreaName.c_str(), "town") != NULL || strstr(g_Robot->NumberedAreaName.c_str(), "Hideout") != NULL)
					g_Robot->InTown = true;
				else
					g_Robot->InTown = false;

				if (strstr(g_Robot->NumberedAreaName.c_str(), "_SideArea") != NULL)
				{
					printf("[OKPOE LOG] Entered Vaal side area...\n");
				}

				printf("[OKPOE LOG] New area: %s (level %d)\n", areaName, areaLevel);
				
				g_Robot->HandleOnAreaChange(); //do we neeed to call this BEFORE changing maps??
			}
		}	
	}
	else if (strstr(msg, "You have entered") != NULL)
	{
		char AreaReadableName[50] = { 0 };
		auto substr = strstr(msg, "You have entered");

		if (substr != NULL)
		{
			int result = sscanf(substr, "You have entered %s.", AreaReadableName);

			if (result)
			{
				if (AreaReadableName[strlen(AreaReadableName) - 1] == '.')
					AreaReadableName[strlen(AreaReadableName) - 1] = '\0';

				g_Robot->ReadableAreaName = string(AreaReadableName);
			}
		}

		g_Robot->Disconnected = false;
		g_Robot->Attacker->IsBusy = false;
		//g_Robot->IsBusy = false;
		g_Robot->ChangingArea = false;
	
	}
	else if (strstr(msg, "Abnormal disconnect: An unexpected disconnection occurred.") != NULL)
	{
		g_Robot->Disconnected = true;

		//kill threads
		//TerminateThread(g_Robot->Attacker->Thread, 0);
	}
	else if (strstr(msg, "0 monsters remain.") != NULL) //map is cleared
	{
		printf("[OKPOE] Map is cleared!\n");
	}

	if (g_Robot->AutoTrading)
	{
		if (!g_Robot->AutoTrade->IsInTrade)
		{
			if (strstr(msg, "Hi, I would like to buy your") != NULL) //... buy your X listed for Y ITEMS in Z (stash tab "A"; position: left 11, top 21)
			{
				if (ExtractWhisperData(msg))
				{		
					FileIO::WriteColorTextConsole("[TRADE BOT] Starting...\n", FOREGROUND_GREEN);
					g_Robot->AutoTrade->IsInTrade = true;
					//set the item info and player info here, handle the rest in new thread.
					g_Robot->AutoTrade->TaskThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)AutoSell, 0, 0, 0);
				}	
			}
		}				
	}
}

bool FileIO::ExtractWhisperData(char* msg)
{
	if (msg == NULL)
		return false;

	auto substr = strstr(msg, "@From ");

	if (substr == NULL)
		return false;

	char* split = strtok(substr, " ");
	
	if (split == NULL)
		return false;

	int counter = 0;

	int requestQuantity = 0;
	int recieveQuantity = 0;

	int StashCellX = 0;
	int StashCellY = 0;

	string playerName;
	string ourItem;
	string exchangeItemName;
	string server;
	string stashTabName;

	bool isReadingPlayerName = false;
	bool isReadingItemName = false;
	bool isReadingQuantity = false;
	bool isReadingExchangeItemName = false;
	bool isReadingExchangeQuantity = false;
	bool isReadingServer = false;
	bool isReadingTabName = false;
	bool isReadingCellX = false;
	bool isReadingCellY = false;

	//@From Souyk: Hi, I'd like to buy your 25 chaos for my 225 alchemy in Scourge.  <- for currency trades
	//@From %s: Hi, I would like to buy your %s* listed for %d %s* in %s (stash tab \"%s\"; position: left %d, top %d)  <- for item trades
	while (split != NULL)
	{
		if (strcmp(split, "your") == 0)
		{
			isReadingQuantity = true;

			split = strtok(NULL, " ");
			continue;
		}
		else if (strcmp(split, "listed") == 0)
		{
			isReadingItemName = false;
			split = strtok(NULL, " ");
			continue;
		}
		else if (strcmp(split, "for") == 0)
		{
			isReadingExchangeQuantity = true;

			split = strtok(NULL, " ");
			continue;
		}
		else if (strcmp(split, "my") == 0)
		{
			isReadingExchangeQuantity = true;

			split = strtok(NULL, " ");
			continue;
		}
		else if (strcmp(split, "in") == 0)
		{
			isReadingExchangeItemName = false;
			isReadingServer = true;

			split = strtok(NULL, " ");
			continue;
		}
		else if (strcmp(split, "(stash") == 0)
		{
			isReadingServer = false;
		}
		else if (strcmp(split, "tab") == 0)
		{
			isReadingTabName = true;
		}
		else if (strcmp(split, "position:") == 0)
		{
			isReadingTabName = false;
		}
		else if (strcmp(split, "left") == 0)
		{
			isReadingCellX = true;
		}
		else if (strcmp(split, "top") == 0) //last read...
		{
			isReadingCellX = false;
			isReadingCellY = true;
		}
		else if (strcmp(split, "@From") == 0)
		{
			isReadingPlayerName = true;
			split = strtok(NULL, " ");
			continue;
		}
		
		if (isReadingPlayerName)
		{
			int lastIndex = strlen(split);
			split[lastIndex] = '\0';
			
			playerName = string(split);
			isReadingPlayerName = false;
		}
		else if (isReadingQuantity)
		{
			if (split[0] >= '0' && split[0] <= '9')
			{
				requestQuantity = atoi(split); //careful..
			}
			else
			{
				ourItem = string(split);
			}

			isReadingQuantity = false;
			isReadingItemName = true;

		}
		else if (isReadingItemName)
		{
			if (ourItem.size() == 0)
			{
				ourItem = string(split);
			}
			else
			{
				ourItem = ourItem + " " + split;
			}
		}
		else if (isReadingExchangeItemName)
		{
			if (exchangeItemName.size() == 0)
			{
				exchangeItemName = string(split);
			}
			else
			{
				exchangeItemName = exchangeItemName + " " + split;
			}	
		}
		else if (isReadingExchangeQuantity)
		{
			if (split[0] >= '0' && split[0] <= '9')
			{
				recieveQuantity = atoi(split); 
			}
			else
			{
				exchangeItemName = string(split);
			}

			isReadingExchangeQuantity = false;
			isReadingExchangeItemName = true;
		}
		else if (isReadingServer)
		{
			int lastIndex = strlen(split);
			split[lastIndex] = '\0';
			
			server = string(split);
			printf("server: %s\n", server.c_str());
			isReadingServer = false;
		}
		else if (isReadingTabName) 
		{
			if (stashTabName.size() == 0)
			{
				stashTabName = string(split);
			}
			else
			{
				stashTabName = stashTabName + " " + split;
			}
		}
		else if (isReadingCellX)
		{
			if (split[0] >= '0' && split[0] <= '9')
			{
				StashCellX = atoi(split); 
			}
		}
		else if (isReadingCellY)
		{
			if (split[0] >= '0' && split[0] <= '9')
			{
				StashCellY = atoi(split);
			}
		}

		split = strtok(NULL, " ");
	}

	if (playerName.size() == 0 || ourItem.size() == 0 || exchangeItemName.size() == 0)
		return false;

	if (requestQuantity == 0) //no number in the whisper implies 1 of the item
		requestQuantity = 1;

	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;

	//server.erase(remove(server.begin(), server.end(), L"."), server.end());

	g_Robot->AutoTrade->OurItemName = conv.from_bytes(ourItem);
	g_Robot->AutoTrade->TradingPlayerName = conv.from_bytes(playerName);
	g_Robot->AutoTrade->TheirItemName = conv.from_bytes(exchangeItemName);
	g_Robot->AutoTrade->server = string(server);

	g_Robot->AutoTrade->TradingPlayerName.erase(remove(g_Robot->AutoTrade->TradingPlayerName.begin(), g_Robot->AutoTrade->TradingPlayerName.end(), L':'), g_Robot->AutoTrade->TradingPlayerName.end());

	g_Robot->AutoTrade->OurQuantity = requestQuantity;
	g_Robot->AutoTrade->TheirItemQuantity = recieveQuantity;

	wprintf(L"playerName: %s\n", g_Robot->AutoTrade->TradingPlayerName.c_str());
	wprintf(L"ourItem: %s\n", g_Robot->AutoTrade->OurItemName.c_str());
	wprintf(L"theirItem: %s\n", g_Robot->AutoTrade->TheirItemName.c_str());
	
	printf("server: %s\n", server.c_str());
	printf("recieveQuantity: %d\n", g_Robot->AutoTrade->TheirItemQuantity);
	printf("requestQuantity: %d\n", g_Robot->AutoTrade->OurQuantity);

	printf("Tab: %s\n", stashTabName.c_str());
	printf("X: %d\n", StashCellX);
	printf("Y: %d\n", StashCellY);

	return true;
}

void FileIO::WriteColorTextConsole(char* msg, short color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_INTENSITY | color));
	FileIO::Log("%s", msg);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (0 | 15)); // 0 or 15 = 15 (0 / 11111)
}

std::list<string> FileIO::GetAllLines(char* fileName)
{
	std::list<string> strings;

	std::ifstream infile(fileName);
	std::string line;

	if (infile.bad())
	{
		printf("[ERROR] Couldn't read/find during GetAllLines\n");
		return (list<string>)NULL;
	}

	while (std::getline(infile, line)) //make this more portable
	{
		strings.push_back(line);
	}

	infile.close();

	return strings;
}

void FileIO::WriteToFile(char* fileName, LPBYTE data, int size)
{
	std::ofstream binFile;

	if (fileName != NULL)
		binFile = std::ofstream(fileName, std::ios::app);

	for (int i = 0; i < size; i++)
	{
		binFile << data[i];
	}

	binFile.close();
}