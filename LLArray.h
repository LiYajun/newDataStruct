//  LLArray.h
//  newDataStructPro
//
//  Created by li yajun on 17/1/4.
//  Copyright 2017 li yajun. All rights reserved.
//

#ifndef LLArray_h
#define LLArray_h


#include <stdio.h>
#include "LLTypes.h"
#include "LLRef.h"


typedef struct _LLArray{
    LLRef      ref; 
    uint       maxCap; 
    uint       objSize;    
    uint       headIndex;  
    uint       tailNextIndex;   
    LLRefPtr *    objects;  
}LLArray;


extern LLArray * LLArrayCreateByCap(sint initCap);
extern LLArray * LLArrayCreate(void);
extern LLRefPtr LLArrayInit(LLRefPtr const ptr, DeallocFunc deallocFunPtr);
 
extern void LLArrayAddObject( LLArray* const p, LLRefPtr anObjct );
 
extern void LLArrayInsertAt(LLArray * const p, LLRefPtr anObject, uint index);
 
extern BOOL LLArrayRemoveAt(LLArray * const p, uint index);
 
extern LLRefPtr LLArrayGetObjectAt(LLArray* const p, uint index);

extern void LLArrayDealloc(LLRefPtr const ptr);


#endif /* LLArray_h */
