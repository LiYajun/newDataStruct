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

#endif /* LLArray_h */
