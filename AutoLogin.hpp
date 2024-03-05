#pragma once
#include <Windows.h>
#include <string>

using namespace std;

class AutoLogin
{
public:

	bool ParseCommandLine();

	static void Login(string username, string password);
	static void SelectCharacter(int index);

	wstring GetAccountName() { return this->AccountName; }
	wstring GetPassword() { return this->Password; }
	int GetCharacterIndex() { return this->CharacterIndex; }

	string ScriptToRun;

private:

	wstring CommandLine;


	wstring AccountName;
	wstring Password;

	int CharacterIndex;


};