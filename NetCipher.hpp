#pragma once
#include <Windows.h>

namespace NetCipher
{
	const byte XorKey = 0xF3;

	byte* CipherString(char* Input);
}