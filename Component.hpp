#pragma once
#include <Windows.h>
#include <stdio.h>
#include <string>

class Component
{
public:

	UINT64 GetAddress() { return this->MemoryAddress; }
	
	std::string GetName() { return this->Name; }
	
	int GetIndex() { return this->ListIndex; }

	void SetIndex(int index) { this->ListIndex = index; }

	void SetName(std::string name) { this->Name = std::string(name); }

	void SetParentAddress(UINT64 addr) { this->EntityParentAddress = addr; }

private:
	
	std::string Name;
	
	int ListIndex;
	
	UINT64 MemoryAddress;
	UINT64 EntityParentAddress;
	UINT64 ComponentListAddress; //used to fetch currentAddress
	//Entity* Parent;
};