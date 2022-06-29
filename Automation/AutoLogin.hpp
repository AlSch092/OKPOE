#pragma once
#include <Windows.h>
#include <string>

using namespace std;

class AutoLogin
{
public:

	bool ParseCommandLine(); //we can make a process manager program which passes the user + password and characterName inside the command line arguments of the launched process, giving us all the info we need

  
	static void Login(string username, string password);
	static void SelectCharacter(int index);

	wstring GetAccountName() { return this->AccountName; }
	wstring GetPassword() { return this->Password; }
  wstring GetCharacterDisplayName() { return this->CharacterDisplayName; }
  int GetCharacterIndex() { return this->CharacterIndex; }

  string GetScriptToRunAfterLogin() { return this->ScriptToRun; }
  
private:

	wstring CommandLine;


	wstring AccountName;
	wstring Password;

	int CharacterIndex;
  wstring CharacterDisplayName;

  string ScriptToRun; //upon loading into the game, we can run a desired script to begin automation process.. part of commandLine

};
