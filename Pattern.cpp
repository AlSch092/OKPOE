#include "Pattern.hpp"

BOOL Check(const BYTE* pData, const BYTE* bMask, const char* szMask) {
	for (; *szMask; ++szMask, ++pData, ++bMask)
	if (*szMask != '?' && *pData != *bMask)
		return false;

	return (*szMask) == NULL;
}

UINT64 FindPattern(const BYTE *bMask, const char* szMask, UINT64 dwOffset, UINT64 dwStartAddress)
{
	DWORD dwLen = 0x010000000000;
	__try
	{
		for (DWORD i = 0; i < dwLen; i++)
		if (Check((BYTE*)(dwStartAddress + i), bMask, szMask))
			return (UINT64)(dwStartAddress + i + dwOffset);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		MessageBox(NULL, TEXT("Pattern Error"), TEXT("Error"), MB_OK);
	}

	return 0;
}