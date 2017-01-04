//
//  LLArray.c
//  newDataStructPro
//
//  Created by li yajun on 17/1/4.
//  Copyright © 2017年 li yajun. All rights reserved.

#include "LLArray.h"
#include "mem_allocator.h"
#include "LLTypes.h"
#include "LLRef.h"

#define  INIT_CAP    8          /*初始化的内存容量*/

static void LLArrayDealloc(void * ptr);

LLArray * LLArrayCreate(void) { 
	return LLArrayCreateByCap(INIT_CAP);
}
LLArray * LLArrayCreateByCap(uint initCap)
{
    LLArray* p = NULL;
    
    if( initCap <= 0) {
        initCap  = INIT_CAP;
    }
    
    p = (LLArray*)Malloc(sizeof(LLArray));
    
    if(p == NULL){
        return NULL;
    }
    LLRefInit(p, LLArrayDealloc);
    p->objects = NULL;
    p->objects = (LLRefPtr*)Malloc(sizeof(LLRefPtr) * initCap);
    
    if(p->objects == NULL){
        LLRefRelease(p);
        return NULL;
    }
    
    p->maxCap     = initCap;
    p->objSize    = 0;
    p->headIndex  = 0;
    p->tailIndex  = 0;
    
    return p;

}

static void LLArrayDealloc(void * ptr)
{
    LLArray * pArray = (LLArray *) ptr;
    if(pArray->objects!=NULL) {
        //释放数组中的对象
    }
}
