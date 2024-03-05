#include "NetCipher.hpp"

byte* NetCipher::CipherString(char* Input)
{
	int length = strlen(Input);

	byte* CipherString = new byte[length];

	for (int i = 0; i < length; i++)
	{
		CipherString[i] = Input[i] ^ NetCipher::XorKey;
	}

	return CipherString;
}