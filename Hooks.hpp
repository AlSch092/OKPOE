#pragma once
#include <Windows.h>
#include "disasm-lib/mhook.h"

typedef void(__fastcall* _Hook)();

BOOL WINAPI SetHook(UINT64 HookAddress, PVOID HookFunc);
VOID RemoveHook(UINT64 HookAddress, INT ByteLength, BYTE* OriginalBytes);

