//
//  LLTArray.h
//  newDataStructPro
//
//  Created by li yajun on 17/1/9.
//  Copyright © 2017年 li yajun. All rights reserved.
//

#ifndef LLTArray_h
#define LLTArray_h
#include "LLArray.h"

typedef struct _LLTArray{
    LLArray array;
    int     myID;
}LLTArray;

extern LLTArray * LLTArrayCreate(void);

extern void LLTArrayDealloc(void * const p);
#endif /* LLTArray_h */
