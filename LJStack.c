#include "LJStack.h"

extern LJStack * LJStackCreateByCap(sint cap)
{
	return LLArrayCreateByCap(cap);
}
extern void  LJStackPush(LJStack * p, LLRefPtr obj)
{
	LLArrayAddObject(p, obj);
}
extern LLRefPtr LJStackPop(LJStack * p)
{
	if (p->objSize <= 0)
		return NULL;

	LLRefPtr obj = LLArrayGetObjectAt(p, p->objSize-1);
	LLRefRetain(obj);
	LLArrayRemoveAt(p, p->objSize - 1);
	return obj;
}


