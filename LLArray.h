//
//  LLArray.h
//  newDataStructPro
//
//  Created by li yajun on 17/1/4.
//  Copyright © 2017年 li yajun. All rights reserved.
//

#ifndef LLArray_h
#define LLArray_h


#include <stdio.h>
#include "LLTypes.h"
#include "LLRef.h"


typedef struct _LLArray{
    LLRef      ref;                /*引用计数*/
    uint       maxCap;             /*最大的内存容量  */
    uint       objSize;            /*现在的元素个数  */
    uint       headIndex;          /*头部的索引     */
    //uint       tailIndex;          /*尾部的索引     */
    uint       tailNextIndex;      /*尾部索引的下一个位置*/
    LLRefPtr *    objects;            /*所有元素       */
}LLArray;

extern LLArray * LLArrayCreateByCap(sint initCap);
extern LLArray * LLArrayCreate(void);
extern void * LLArrayInit(void * const ptr, deallocFun deallocFunPtr);
//末尾添加一个元素
extern void LLArrayAddObject( LLArray* const p, LLRefPtr anObjct );
//插入一个元素
extern void LLArrayInsertAt(LLArray * const p, LLRefPtr anObject, uint index);
//删除一个元素
extern BOOL LLArrayRemoveAt(LLArray * const p, uint index);
//获取一个元素
extern LLRefPtr LLArrayGetObjectAt(LLArray* const p, uint index);

extern void LLArrayDealloc(void * const ptr);

#endif /* LLArray_h */
