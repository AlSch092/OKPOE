#pragma once
#include "Structures.hpp"

//ASM Hooks
extern "C" void OutPacketHook();
extern "C" void EntitySpawnHook();
extern "C" void EntityLabelSpawnHook();

extern "C" void InitializeHotkeyVars(UINT64 _returnAddr, UINT64 callback);
extern "C" void HotkeyHook();

extern "C" void CPUReduceHook();

extern "C" void MinimapIconsHook();

extern "C" void ClientMessageHook();

extern "C" void OnSkillGemLevelUpHook();

//Utility
extern "C" UINT64 GetSendClass();

//ASM Game Funcs
extern "C" void SendPacket(UINT64 SendClass, LPBYTE Data, UINT64 Length);
extern "C" void SendAction(UINT64 ptrState, UINT16 SkillID, UINT64 optional_entity, Vector2* v2);
extern "C" void SetCPUReducerTime(int time);

