#include "LSArray.h"
#include <math.h>


static const uint DEF_CAP   = 8;


void LSArrayRetain(LSRefPtr ptr);

void LSArrayRelease(LSRefPtr ptr);

void LSArrayDealloc(LSRefPtr ptr);

void LSArrayDisplay(LSRefPtr ptr, uint offset);

BOOL LSArrayCheckCap(LSArray *arr);

BOOL LSArrayCoverMem(LSRefPtr dst, LSRefPtr src, uint count);


LSArray *LSArrayCreate()
{
    return LSArrayCreateByCap(DEF_CAP);
}

LSArray *LSArrayCreateByCap(uint cap)
{
    LSArray *pArray = NULL;

    if (!(pArray = (LSArray *)Malloc(sizeof(LSArray))))
    {
        return NULL;
    }

    cap = max(DEF_CAP, cap);
    if (!(pArray->objects = (LSRefPtr *)Malloc(sizeof(LSRefPtr) * cap)))
    {
        Free(pArray);
        return NULL;
    }

    LSInit(pArray, LSArrayRetain, LSArrayRelease, LSArrayDealloc, LSArrayDisplay);
    pArray->capacity    = cap;
    pArray->size        = 0;

    return pArray;
}

BOOL LSArrayAdd(LSArray *const ptr, LSRefPtr obj)
{
    return LSArrayInsert(ptr, obj, ptr->size);
}

BOOL LSArrayInsert(LSArray *const ptr, LSRefPtr obj, uint index)
{
    if (!ptr || !obj || !LSArrayCheckCap(ptr))
    {
        return NO;
    }

    index = min(index, ptr->size);
    if (index < ptr->size)
    {
        LSRefPtr dst = ptr->objects + index + 1;
        LSRefPtr src = ptr->objects + index;
        uint count = ptr->size - index;
        if (!LSArrayCoverMem(dst, src, count))
        {
            return NO;
        }
    }

    LSRetain(obj);
    ptr->objects[index] = obj;
    ptr->size++;

    return YES;
}

BOOL LSArrayRemove(LSArray *const ptr, uint index)
{
    LSRefPtr obj = LSArrayGet(ptr, index);
    if (!obj)
    {
        return NO;
    }
    
    if (index < ptr->size - 1)
    {
        LSRefPtr dst = ptr->objects + index;
        LSRefPtr src = ptr->objects + index + 1;
        uint count = ptr->size - index - 1;
        if (!LSArrayCoverMem(dst, src, count))
        {
            return NO;
        }
    }

    LSRelease(obj);
    ptr->size--;

    return YES;
}

LSRefPtr LSArrayGet(LSArray *const ptr, uint index)
{
    if (!ptr || ptr->size <= index)
    {
        return NULL;
    }

    return ptr->objects[index];
}

void LSArrayRetain(LSRefPtr ptr)
{
    LSArray *pArray = (LSArray *)ptr;

    for (uint i = 0; i < pArray->size; i++)
    {
        LSRetain(pArray->objects[i]);
    }
}

void LSArrayRelease(LSRefPtr ptr)
{
    LSArray *pArray = (LSArray *)ptr;

    for (uint i = 0; i < pArray->size; i++)
    {
        LSRelease(pArray->objects[i]);
    }
}

void LSArrayDealloc(LSRefPtr ptr)
{
    LSArray *pArray = (LSArray *)ptr;

    Free(pArray->objects);
    
    printf("LSArray Dealloc\n");
}

void LSArrayDisplay(LSRefPtr ptr, uint offset)
{
    char *ss = (char *)Malloc(offset + 1);
    MemSet(ss, '-', offset);
    ss[offset] = 0;

    printf("%saddr:%p, retainCount:%u\n", ss, ptr, ((LSRef *)ptr)->retainCount);

    Free(ss);

    LSArray *pArray = (LSArray *)ptr;
    for (uint i = 0; i < pArray->size; i++)
    {
        LSRef *pRef = (LSRef *)pArray->objects[i];
        if (pRef->display)
        {
            pRef->display(pRef, offset + 2);
        }
    }
}


BOOL LSArrayCheckCap(LSArray *arr)
{
    if (arr->capacity > arr->size)
    {
        return YES;
    }

    LSRefPtr *newObjs = (LSRefPtr *)Malloc(sizeof(LSRefPtr) * arr->capacity * 2);
    if (!newObjs)
    {
        return NO;
    }

    MemCpy(newObjs, arr->objects, arr->size);
    Free(arr->objects);
    arr->objects = newObjs;
    arr->capacity *= 2;

    return YES;
}

BOOL LSArrayCoverMem(LSRefPtr dst, LSRefPtr src, uint count)
{
    LSRefPtr *temp = (LSRefPtr *)Malloc(sizeof(LSRefPtr) * count);
    if (!temp)
    {
        return NO;
    }

    MemCpy(temp, src, count);
    MemCpy(dst, temp, count);
    Free(temp);

    return YES;
}
