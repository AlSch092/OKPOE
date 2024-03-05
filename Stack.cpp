#include "Stack.hpp"

int Stack::GetStackSize(Entity* e)
{
	UINT64 CompAddr = e->GetComponentAddress("Stack");
	int Count = 0;

	if (CompAddr == 0)
	{
		return 0; //return 1 stack size if the component doesnt exist, implies a single item
	}

	Count = DereferenceSafe<UINT>(CompAddr + Stack::CurrentCountOffset);

	return Count;
}
