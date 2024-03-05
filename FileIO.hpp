#pragma once
#include <string>
#include <fstream>
#include <stdio.h>
#include "AutoTrader.hpp"


namespace FileIO
{
	bool FileHasLine(wchar_t* FilePath, const wchar_t* Substring);
	void FileLog(const char* format, ...);
	void WLog(const wchar_t* format, ...);
	void Log(const char* format, ...);
	int GetDesiredSocketsFromFile(wchar_t* FilePath, wchar_t* Substring);
	int GetDesiredLinksFromFile(wchar_t* FilePath, wchar_t* Substring);

	void ClientMessageHook(void* StackPtrUnk, int fileMode, char* msg, int msgSizeBytes);

	bool ExtractWhisperData(char* msg); //for autotrader

	void WriteColorTextConsole(char* msg, short color);

	std::list<string> GetAllLines(char* fileName);

	void WriteToFile(char* fileName, LPBYTE data, int size);
}