#pragma once
#include "MultiClient.hpp"
#include <iostream>

struct SYSTEM_HANDLE_INFORMATION {
	UINT64 pid;
	BYTE type;
	BYTE flags;
	WORD handle;
	DWORD object;
	DWORD access;
};

typedef struct _OBJECT_NAME_INFORMATION {
	UNICODE_STRING Name;
} OBJECT_NAME_INFORMATION, *POBJECT_NAME_INFORMATION;

typedef NTSTATUS(NTAPI *NtQuerySystemInformation_t) (SYSTEM_INFORMATION_CLASS SystemInformationClass, PVOID SystemInformation, ULONG SystemInformationLength, PULONG ReturnLength);
typedef NTSTATUS(NTAPI *NtQueryObject_t) (HANDLE Handle, OBJECT_INFORMATION_CLASS ObjectInformationClass, PVOID ObjectInformation, ULONG ObjectInformationLength, PULONG ReturnLength);

VOID MultiTrue() {
	while (!EnableMulti(L"PoERunMutexA")) {
		Sleep(100);
	}
}

BOOL EnableMulti(wchar_t* mutantName) {

	int handleCount = 1024;

	HMODULE ntdll = GetModuleHandleW(L"ntdll");
	if (ntdll == NULL) {
		return false;
	}

	NtQueryObject_t ntQO = (NtQueryObject_t)GetProcAddress(ntdll, "NtQueryObject");
	NtQuerySystemInformation_t ntQSI = (NtQuerySystemInformation_t)GetProcAddress(ntdll, "NtQuerySystemInformation");
	if (ntQO == NULL || ntQSI == NULL) {
		printf("[MultiClient] GetProcAddress failed!\n");
		return false;
	}

	struct HandleInfoSet {
		unsigned int count;
		SYSTEM_HANDLE_INFORMATION handles[1];
	};

	HandleInfoSet *infoSet = (HandleInfoSet *)malloc(4 + sizeof(SYSTEM_HANDLE_INFORMATION) * handleCount);
	DWORD length;

	NTSTATUS status = ntQSI((SYSTEM_INFORMATION_CLASS)16, infoSet, 4 + sizeof(SYSTEM_HANDLE_INFORMATION) * handleCount, &length);

	while (status == 0xc0000004 /*STATUS_INFO_LENGTH_MISMATCH*/) {
		free(infoSet);
		handleCount *= 2;
		infoSet = (HandleInfoSet *)malloc(4 + sizeof(SYSTEM_HANDLE_INFORMATION) * handleCount);
		status = ntQSI((SYSTEM_INFORMATION_CLASS)16, infoSet, 4 + sizeof(SYSTEM_HANDLE_INFORMATION) * handleCount, &length);
		printf("Status: %x\n", status);
	}

	if (status != 0 /*STATUS_SUCCESS*/) {
		free(infoSet);
		printf("Multi failed at status != 0");
		return false;
	}

	printf("infoSet->count: %d\n", infoSet->count);

	for (unsigned int i = 0; i < infoSet->count; i++) {
		
		wchar_t nameBuffer[1024];
		printf("Infoset->handles[%d] = %d, pid: %x\n", i, infoSet->handles[i].handle, infoSet->handles[i].pid);

		if (infoSet->handles[i].handle == 0x0012019F) continue;	// some buggy thing we need to skip
		
		status = ntQO((HANDLE)infoSet->handles[i].handle, (OBJECT_INFORMATION_CLASS)1, nameBuffer, 1024, &length);
		
		if (status != 0 /*STATUS_SUCCESS*/)
			continue;

		if (wcsstr(nameBuffer, mutantName) != NULL) {
			wprintf(L"nameBuffer: %s\n", nameBuffer);

			HANDLE handle;
			if (!DuplicateHandle(GetCurrentProcess(), (HANDLE)infoSet->handles[i].handle, 0, &handle, 0, FALSE, DUPLICATE_CLOSE_SOURCE))
			{
				printf("DuplicateHandle failed: %d\n", GetLastError());
			}

			CloseHandle(handle);
			free(infoSet);
			return true;
		}
	}

	free(infoSet);
	return false;
}