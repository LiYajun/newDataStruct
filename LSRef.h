#ifndef __LSREF_H__
#define __LSREF_H__


#include "LLTypes.h"
#include "mem_allocator.h"
#include <stdio.h>


typedef void *LSRefPtr;


/************************************************************************\
 函数指针                                                                    
\************************************************************************/
typedef void(*DeallocFunc)(LSRefPtr pRef);
                                                              
typedef void(*DisplayFunc)(LSRefPtr pRef, uint offset);


/************************************************************************\
 基类                                                                  
\************************************************************************/
typedef struct
{
    sint            retainCount;
    DeallocFunc     dealloc;
    DisplayFunc     display;
} LSRef;

LSRef *LSRefCreate(void);

LSRefPtr LSRefRetain(LSRefPtr ptr);

void LSRefRelease(LSRefPtr ptr);


/************************************************************************\
 通用方法                                                        
\************************************************************************/
LSRef *LSInit(LSRefPtr ptr,
              DeallocFunc deallocF,
              DisplayFunc displayF);

void LSDisplay(LSRefPtr ptr);


/************************************************************************\
 通用宏                                                                    
\************************************************************************/
#define LS_RETAIN(ptr)          LSRefRetain(ptr)

#define LS_RELEASE(ptr)         LSRefRelease(ptr); \
                                ptr = NULL


#endif // !__LSREF_H__
