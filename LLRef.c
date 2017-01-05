#include "LLRef.h"
#include "mem_allocator.h"



//释放前的的回调函数
static void LLRefDealloc(void * ptr)
{
    fprintf(stdout, "LLRefDealloc called!");
}

LLRef * LLRefCreate(void)
{
	LLRef * pRef = (LLRef*)Malloc(sizeof(LLRef));

	if(pRef)
    {
		LLRefInit(pRef,  LLRefDealloc);
	}

	return pRef;
}

void LLRefInit(void * ptr, deallocFun deallocFunPtr)
{
	LLRef * pRef = (LLRef*)ptr;
	pRef->retainCount = 1;
    pRef->dealloc     = deallocFunPtr;
}

void setDealloc(void * ptr, deallocFun funPtr)
{
    LLRef * pRef = (LLRef*)ptr;
    pRef->dealloc = funPtr;
}

sint LLRefRelease(void * ptr)
{
	LLRef * pRef = (LLRef*)ptr;

	if (pRef->retainCount>0) 
    {
		pRef->retainCount--;
	}

	sint count = pRef->retainCount;

	if (pRef->retainCount == 0) 
    {
        if(pRef->dealloc!=NULL)
            pRef->dealloc(pRef);
        
		Free(pRef);
	}

	return count;
}

sint LLRefRetain(void * ptr)
{
	LLRef * pRef = (LLRef*)ptr;
	pRef->retainCount++;
	return pRef->retainCount;
}
