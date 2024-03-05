#include "Hooks.hpp"

BOOL WINAPI SetHook(UINT64 HookAddress, PVOID HookFunc) {

	_Hook hook = (_Hook)HookAddress;

	return Mhook_SetHook((PVOID*)&hook, HookFunc);
}

VOID RemoveHook(UINT64 HookAddress, INT ByteLength, BYTE* OriginalBytes)
{
	DWORD dwOldProt;
	VirtualProtect((LPVOID)HookAddress, ByteLength, PAGE_EXECUTE_READWRITE, &dwOldProt);
	memcpy((void*)HookAddress, (void*)OriginalBytes, ByteLength);
	VirtualProtect((LPVOID)HookAddress, ByteLength, dwOldProt, &dwOldProt);
}
