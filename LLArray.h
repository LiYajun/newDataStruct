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
    uint       tailIndex;          /*尾部的索引     */
    LLRefPtr *    objects;            /*所有元素       */
}LLArray;

extern LLArray * LLArrayCreateByCap(sint initCap);
extern LLArray * LLArrayCreate(void);



//添加一个元素
extern void LLArrayInsertAt(LLArray * const p, LLRefPtr anObject, uint index);
//删除一个元素
extern BOOL LLArrayRemoveAt(LLArray * const p, uint index);
//获取一个元素
extern LLRefPtr LLArrayGetObjectAt(LLArray* const p, uint index);
//获取一组元素


#endif /* LLArray_h */
