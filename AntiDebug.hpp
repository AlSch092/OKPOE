#pragma once
#include "NetLogger.hpp"

namespace AntiDebug
{
	static bool bIsDebuggerPresent = false;

	void LoopDebugChecks();

	static bool IsDebuggerPresent_1();
	static bool IsDebuggerPresent_2();
	static bool IsDebuggerPresent_3();
};
