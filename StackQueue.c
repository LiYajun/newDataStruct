#include "StackQueue.h"
#include "mem_allocator.h"
static void popStackToOther(NumStack * srcStack, NumStack * destStack);
NumQueue * createQueue(sint num)
{
	NumQueue * ptr = Malloc(sizeof(NumQueue));
	ptr->stackIn = createStack(num );
	ptr->stackOut = createStack(num);
	ptr->maxCap  = num;
	ptr->curSize = 0;
	return  ptr;
}

BOOL appendTail(NumQueue * ptr, sint value)
{
	if (ptr->stackOut->curSize > 0)
	{
		popStackToOther(ptr->stackOut, ptr->stackIn);
	}
	BOOL flag = stackPush(ptr->stackIn, value);
	ptr->curSize++;
	return flag;
}
 
sint deleteHead(NumQueue * ptr)
{
	if (ptr->stackIn->curSize > 0)
	{
		popStackToOther(ptr->stackIn, ptr->stackOut);
	}
	sint value = stackPop(ptr->stackOut);
	ptr->curSize--;
	return value;
}
void QueueClear(NumQueue * ptr)
{
	if (ptr==NULL) return;
	stackClear(ptr->stackIn);
	stackClear(ptr->stackOut);
	Free(ptr);
}
void popStackToOther(NumStack * srcStack, NumStack * destStack)
{
	uint num = srcStack->curSize;
	for (uint i = 0; i < num; i++)
	{
		sint value = stackPop(srcStack);
		stackPush(destStack, value);
	}
}