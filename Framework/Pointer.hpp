#pragma once
#include <Windows.h>

template<class T>
T ReadPointer(UINT64 ulBase, int iOffset)
{
	__try
	{
		return *(T*)(*(UINT64*)ulBase + iOffset);
	}
	__except (EXCEPTION_EXECUTE_HANDLER) { return (T)NULL; }
}

template<class T>
bool WritePointer(UINT64 ulBase, UINT64 iOffset, T iValue)
{
	__try { *(T*)(*(UINT64*)ulBase + iOffset) = iValue; return true; }
	__except (EXCEPTION_EXECUTE_HANDLER) { return false; }
}

template<class T>
T DereferenceSafe(UINT64 ulAddress)
{
	__try
	{
		return *(T*)ulAddress;
	}
	__except (EXCEPTION_EXECUTE_HANDLER) { return (T)NULL; }
}

template<class T>
T DereferenceSafeWithAddedOffset(UINT64 ulAddress, INT64 Offset)
{
	__try
	{
		T val = *(T*)(ulAddress);
		return val;
	}
	__except (EXCEPTION_EXECUTE_HANDLER) { return (T)NULL; }
}

template <class T>
T Write(UINT64 ulAddress, T value) //there is almost no reason to ever write memory on PoE, game is 95% server sided however exploits do exist within that 5% or so that is client-sided
{
	__try
	{
		*(T*)ulAddress = value;
	}
	__except (EXCEPTION_EXECUTE_HANDLER) { return (T)NULL; }
}
