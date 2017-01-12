#include "LLRef.h"
#include "mem_allocator.h"

extern LLRef * LLRefCreate(void)
{
	LLRef * pRef = (LLRef*)Malloc(sizeof(LLRef));

	if(pRef)
    {
		LLRefInit(pRef,  LLRefDealloc);
	}

	return pRef;
}

extern void * LLRefInit(void * ptr, deallocFun deallocFunPtr)
{
	LLRef * pRef = (LLRef*)ptr;
	pRef->retainCount = 1;
    pRef->dealloc     = deallocFunPtr;
    return ptr;
}

extern void setDealloc(void * ptr, deallocFun funPtr)
{
    LLRef * pRef = (LLRef*)ptr;
    pRef->dealloc = funPtr;
}

extern sint LLRefRelease(void * ptr)
{
	LLRef * pRef = (LLRef*)ptr;

    pRef->retainCount--;
	sint count = pRef->retainCount;

	if (pRef->retainCount == 0) 
    {
        if(pRef->dealloc!=NULL)
            pRef->dealloc(pRef);
        
		Free(pRef);
	}

	return count;
}

extern sint LLRefRetain(void * ptr)
{
	LLRef * pRef = (LLRef*)ptr;
	pRef->retainCount++;
	return pRef->retainCount;
}

//释放前的的回调函数
extern void LLRefDealloc(void * ptr)
{
    fprintf(stdout, "LLRefDealloc called\n");
	//printf("%s", __FUNCDNAME__);
}
