#include "Stack.hpp"

int Stack::GetStackSize(Entity* e)
{
	UINT64 CompAddr = e->GetComponentAddress("Stack");
	int Count = 0;

	if (CompAddr == 0)
		return 0;
 
	return DereferenceSafe<UINT>(CompAddr + Stack::CurrentCountOffset);;
}
