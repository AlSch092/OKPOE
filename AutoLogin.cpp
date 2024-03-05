#include "AutoLogin.hpp"

bool AutoLogin::ParseCommandLine()
{
	string sCmdLine = GetCommandLineA();
	string _arguments = sCmdLine.substr(sCmdLine.find(".exe", 4));
	
	printf("args: %s\n", _arguments.c_str());

	if (strlen(_arguments.c_str()) > 5)
	{
		char account[50];
		char password[25];
		int characterIndex;
		char ScriptPath[256];

		//change this to work with proper args
		sscanf(sCmdLine.c_str(), "C:\\Program Files (x86)\\Grinding Gear Games\\Path of Exile\\PathOfExile.exe %s %s %d %s", account, password, &characterIndex, ScriptPath); //easy formatting

		printf("%s %s %d %s\n", account, password, characterIndex, ScriptPath);

		if (strlen(account) > 0)
		{
				//convert to wide
				wchar_t wideAccount[50] = { 0 };
				mbtowc(wideAccount, account, strlen(account));

				if (wcslen(wideAccount) > 0)
				{
					this->AccountName = wideAccount;
				}

				wchar_t widePw[50] = { 0 };
				mbtowc(widePw, password, strlen(password));

				if (wcslen(widePw) > 0)
				{
					this->Password = widePw;
				}
	
				this->CharacterIndex = characterIndex;		
				
				wchar_t wideScriptPath[256] = { 0 };
				mbtowc(wideScriptPath, ScriptPath, strlen(ScriptPath));

				if (strlen(ScriptPath) > 0)
				{
					printf("Script: %s\n", ScriptPath);
				}

				return true;
		}
		else
		{
			printf("[OKP Autologin] Username was NULL!\n");
			return false;
		}
	}

	return false;
}

void AutoLogin::Login(string username, string password)
{


}

void AutoLogin::SelectCharacter(int index)
{

}