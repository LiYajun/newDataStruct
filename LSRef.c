#include "LSRef.h"


void LSRefDealloc(LSRefPtr ptr);

void LSRefDisplay(LSRefPtr ptr, uint offset);


LSRef *LSRefCreate()
{
    LSRef *pRef = (LSRef *)Malloc(sizeof(LSRef));

    if (pRef)
    {
        LSInit(pRef, NULL, NULL, LSRefDealloc, LSRefDisplay);
    }

    return pRef;
}


LSRef *LSInit(LSRefPtr ptr,
              RetainFunc retainF,
              ReleaseFunc releaseF,
              DeallocFunc deallocF,
              DisplayFunc displayF)
{
    LSRef *pRef = (LSRef *)ptr;
   
    pRef->retainCount   = 1;
    pRef->retain        = retainF;
    pRef->release       = releaseF;
    pRef->dealloc       = deallocF;
    pRef->display       = displayF;

    return pRef;
}

sint LSRetain(LSRefPtr ptr)
{
    LSRef *pRef = (LSRef *)ptr;

    if (pRef->retain)
    {
        pRef->retain(pRef);
    }

    pRef->retainCount++;

    return pRef->retainCount;
}

sint LSRelease(LSRefPtr ptr)
{
    sint result = 0;

    LSRef *pRef = (LSRef *)ptr;

    if (pRef->release)
    {
        pRef->release(pRef);
    }

    result = --pRef->retainCount;

    if (result <= 0)
    {
        if (pRef->dealloc)
        {
            pRef->dealloc(pRef);
        }
        Free(pRef);
    }

    return result;
}

void LSDisplay(LSRefPtr ptr)
{
    LSRef *pRef = (LSRef *)ptr;

    if (pRef->display)
    {
        pRef->display(ptr, 0);
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
