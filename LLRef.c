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

extern LLRefPtr LLRefInit(LLRefPtr ptr, DeallocFunc deallocFunPtr)
{
	LLRef * pRef = (LLRef*)ptr;
	pRef->retainCount = 1;
    pRef->dealloc     = deallocFunPtr;
    pRef->display     = NULL;
    return ptr;
}


extern sint LLRefRelease(LLRefPtr ptr)
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

extern sint LLRefRetain(LLRefPtr ptr)
{
	LLRef * pRef = (LLRef*)ptr;
	pRef->retainCount++;
	return pRef->retainCount;
}
extern void LLRefPrint(LLRefPtr ptr)
{
    LLRef *pRef = (LLRef *)ptr;
    
    if (pRef->display) {
        pRef->display(ptr);
    }
}
//
extern void LLRefDealloc(LLRefPtr ptr)
{
    fprintf(stdout, "LLRefDealloc called\n");
}
static void LLRefPrintValues(LLRefPtr ptr)
{
    //print values about LLRef;
    fprintf(stdout,"print values of LLRef:");
}
