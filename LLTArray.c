//
//  LLTArray.c
//  newDataStructPro
//
//  Created by li yajun on 17/1/9.
//  Copyright © 2017年 li yajun. All rights reserved.
//

#include "LLTArray.h"
#include "mem_allocator.h"

void LLTArrayDealloc(void * const p);

void * LLTArrayInit(void * const ptr, deallocFun funPtr);

static uint TArrayID = 0;
extern LLTArray * LLTArrayCreate(void)
{
    LLTArray * ptr = NULL;
    ptr = (LLTArray*)Malloc(sizeof(LLTArray));
    if(ptr==NULL)
        return NULL;
    return   LLTArrayInit(ptr, LLTArrayDealloc);

}
void * LLTArrayInit(void * const ptr, deallocFun funPtr)
{
    LLTArray * p = LLArrayInit(ptr, LLTArrayDealloc);
    
    if(p!=NULL) {
        p->myID  = TArrayID++;
    }
    return p;
}
void LLTArrayDealloc(void * const p)
{
    printf("LLTArrayDealloc called\n");
    LLArrayDealloc(p);
    
  
}
