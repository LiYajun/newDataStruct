#include "LSRef.h"


void LSRefDealloc(LSRefPtr ptr);

void LSRefDisplay(LSRefPtr ptr, uint offset);


LSRef *LSRefCreate()
{
    LSRef *pRef = (LSRef *)Malloc(sizeof(LSRef));

    if (pRef)
    {
        LSInit(pRef, LSRefDealloc, LSRefDisplay);
    }

    return pRef;
}

LSRef *LSInit(LSRefPtr ptr,
              DeallocFunc deallocF,
              DisplayFunc displayF)
{
    LSRef *pRef = (LSRef *)ptr;
   
    pRef->retainCount   = 1;
    pRef->dealloc       = deallocF;
    pRef->display       = displayF;

    return pRef;
}

void LSDisplay(LSRefPtr ptr)
{
    LSRef *pRef = (LSRef *)ptr;

    if (pRef->display)
    {
        pRef->display(ptr, 0);
    }
}


LSRefPtr LSRefRetain(LSRefPtr ptr)
{
    LSRef *pRef = (LSRef *)ptr;

    pRef->retainCount++;

    return pRef;
}

void LSRefRelease(LSRefPtr ptr)
{
    LSRef *pRef = (LSRef *)ptr;

    if (--(pRef->retainCount) <= 0)
    {
        if (pRef->dealloc)
        {
            pRef->dealloc(pRef);
        }

        Free(pRef);
    }
}


void LSRefDealloc(LSRefPtr ptr)
{
    printf("LSRef Deallocn\n");
}

void LSRefDisplay(LSRefPtr ptr, uint offset)
{
    char *ss = (char *)Malloc(offset + 1);
    MemSet(ss, '-', offset);
    ss[offset] = 0;

    printf("%saddr:%p, retainCount:%u\n", ss, ptr, ((LSRef *)ptr)->retainCount);

    Free(ss);
}
