#ifndef __LSREF_H__
#define __LSREF_H__


#include "LLTypes.h"
#include "mem_allocator.h"
#include <stdio.h>


typedef void *LSRefPtr;


// 处理修改引用计数之外的特殊操作   
typedef void(*RetainFunc)(LSRefPtr pRef);
typedef void(*ReleaseFunc)(LSRefPtr pRef);

// 处理除了释放Ref资源外的特殊操作
typedef void(*DeallocFunc)(LSRefPtr pRef);

// 打印操作                                                                
typedef void(*DisplayFunc)(LSRefPtr pRef, uint offset);


/************************************************************************\
 基类                                                                  
\************************************************************************/
typedef struct
{
    sint            retainCount;
    RetainFunc      retain;
    ReleaseFunc     release;
    DeallocFunc     dealloc;
    DisplayFunc     display;
} LSRef;

LSRef *LSRefCreate(void);


/************************************************************************\
 通用方法                                                                    
\************************************************************************/
LSRef *LSInit(LSRefPtr ptr,
              RetainFunc retainF,
              ReleaseFunc releaseF,
              DeallocFunc deallocF,
              DisplayFunc displayF);

sint LSRetain(LSRefPtr ptr);

sint LSRelease(LSRefPtr ptr);

void LSDisplay(LSRefPtr ptr);


#endif // !__LSREF_H__
