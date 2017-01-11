#ifndef __LSARRAY_H__
#define __LSARRAY_H__


#include <stdio.h>
#include "LSRef.h"


typedef struct  
{
    LSRef       base;
    uint        capacity;
    uint        size;
    LSRefPtr    *objects;
} LSArray;


LSArray *LSArrayCreate(void);

LSArray *LSArrayCreateByCap(uint cap);

BOOL LSArrayAdd(LSArray *const ptr, LSRefPtr obj);

BOOL LSArrayInsert(LSArray *const ptr, LSRefPtr obj, uint index);

BOOL LSArrayRemove(LSArray *const ptr, uint index);

LSRefPtr LSArrayGet(LSArray *const ptr, uint index);


#endif // !__LSARRAY_H__
