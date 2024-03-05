#include "OS.hpp"
#include <Lmcons.h>

string OS::GetCurrentUsername()
{
	char username[UNLEN + 1];
	DWORD username_len = UNLEN + 1;
	if (GetUserNameA(username, &username_len))
	{
		string user = username;
		return user;
	}

	return NULL;
}

int OS::GetCPUID()
{
	int regs[4] = { 0 };
	//__cpuid(regs, 0);

	return regs[0];
}


bool OS::IsElevated()
{
	DWORD dwSize = 0;
	HANDLE hToken = NULL;
	bool bReturn = false;;

	TOKEN_ELEVATION tokenInformation;

	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken))
		return FALSE;

	if (GetTokenInformation(hToken, TokenElevation, &tokenInformation, sizeof(TOKEN_ELEVATION), &dwSize))
	{
		bReturn = (bool)tokenInformation.TokenIsElevated;
	}

	CloseHandle(hToken);
	return bReturn;
}

bool OS::SetDebugPrivilege(bool Enable)
{
	HANDLE hToken{ nullptr };
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES, &hToken))
		return false;

	DWORD dwSize = 0;
	TOKEN_ELEVATION tokenInformation;

	if (GetTokenInformation(hToken, TokenElevation, &tokenInformation, sizeof(TOKEN_ELEVATION), &dwSize))
	{
		if (tokenInformation.TokenIsElevated)
			return true; //already elevated
	}

	TOKEN_PRIVILEGES TokenPrivileges{};
	TokenPrivileges.PrivilegeCount = 1;
	TokenPrivileges.Privileges[0].Attributes = Enable ? SE_PRIVILEGE_ENABLED : 0;

	if (!LookupPrivilegeValueA(nullptr, "SeDebugPrivilege", &TokenPrivileges.Privileges[0].Luid))
	{
		CloseHandle(hToken);
		return false;
	}

	if (AdjustTokenPrivileges(hToken, FALSE, &TokenPrivileges, sizeof(TOKEN_PRIVILEGES), nullptr, nullptr) != ERROR_SUCCESS)
	{
		CloseHandle(hToken);
		return false;
	}

	CloseHandle(hToken);

	return true;
}

