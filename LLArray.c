//
//  LLArray.c
//  newDataStructPro
//
//  Created by li yajun on 17/1/4.
//  Copyright © 2017年 li yajun. All rights reserved.

#include "LLArray.h"
#include "mem_allocator.h"
#include <assert.h>

#define  INIT_CAP    8          /*初始化的内存容量*/

static void LLArrayDealloc(void * const ptr);
static void LLArrayInit(LLArray * const ptr, sint cap);
static BOOL LLArrayCheckMaxCap( LLArray* const p);

static void LLArrayForward( LLArray* const p, uint num, uint start);
static void LLArrayBackward( LLArray * const p, uint num ,uint end);

static uint LLArrayGetPreIndex(LLArray * const p, uint index);
static uint LLArrayGetNextIndex(LLArray * const p, uint index);

extern LLArray * LLArrayCreate(void)
{
	return LLArrayCreateByCap(INIT_CAP);
}
extern LLArray * LLArrayCreateByCap(sint initCap)
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
    
    LLArrayInit(p, initCap);
    
    return p;

}

/*---------------------------------------------*\
 插入一个元素
\*---------------------------------------------*/
extern void LLArrayInsertAt( LLArray * const p, LLRefPtr anObject, uint index)
{
    uint realIndex= 0;
    LLRef * object = anObject;
    
    assert(anObject != NULL);
    
    if(index > p->objSize) {
        fprintf(stderr, "index out of array range!");
        return;
    }
    if(LLArrayCheckMaxCap(p) == NO) {
        fprintf(stderr, "failed realloc memory!");
        return ;
    }
    
    //获取实际的插入位置
    realIndex = (p->headIndex+index)% p->maxCap;
    
    if(index <= p->objSize/2) {
        realIndex = LLArrayGetPreIndex(p, realIndex); //实际的位置
        LLArrayForward(p, index, p->headIndex);
        p->objects[realIndex] = object;
        
        p->headIndex  = LLArrayGetPreIndex(p, p->headIndex);
    }else {
        LLArrayBackward(p, p->objSize-index, p->tailIndex);
        p->objects[realIndex] = object;
        
        p->tailIndex = LLArrayGetNextIndex(p, p->tailIndex);
    }
    LLRefRetain(object);
    
    p->objSize++;
}
/*---------------------------------------------*\
 移除一个对象
\*---------------------------------------------*/
extern BOOL LLArrayRemoveAt(LLArray * const p, uint index)
{
    uint realIndex= 0;
    LLRefPtr obj = NULL;
    //assert(p != NULL);
    
    if(index >= p->objSize) {
        fprintf(stderr, "index out of array range! del index form 0  to objsize -1!");
        return NO;
    }
    realIndex = (p->headIndex+index)% p->maxCap;
    obj = p->objects[realIndex];
    if(index <= p->objSize/2) {
        realIndex = LLArrayGetPreIndex(p, realIndex);
        LLArrayBackward(p, index, realIndex);
        p->headIndex = LLArrayGetNextIndex(p, p->headIndex);
    }else {
        realIndex = LLArrayGetNextIndex(p, realIndex);
        LLArrayForward(p, index, realIndex);
        p->tailIndex = LLArrayGetPreIndex(p, p->tailIndex);
    }
    LLRefRelease(obj);
    p->objSize--;
    return YES;
}
/*---------------------------------------------*\
 获取一个对象
\*---------------------------------------------*/
extern LLRefPtr LLArrayGetObjectAt(LLArray* const p, uint index)
{
    uint realIndex= 0;
    
    if(index >= p->objSize) {
        fprintf(stderr, "index out of array range! del index form 0 ~ objsize -1!");
        return NULL;
    }
    realIndex = (p->headIndex+index)% p->maxCap;
    return    p->objects[realIndex];
}
/*---------------------------------------------*\
 初始化
\*---------------------------------------------*/
static void LLArrayInit(LLArray * const ptr, sint cap)
{
    ptr->maxCap     = cap;
    ptr->objSize    = 0;
    ptr->headIndex  = 0;
    ptr->tailIndex  = 0;
}



/*---------------------------------------------*\
 检查容量
\*---------------------------------------------*/
static BOOL LLArrayCheckMaxCap( LLArray* const p )
{
    LLRefPtr * newP = NULL;
    LLRefPtr * oldP = NULL;
    uint realIndex = 0;
    uint i;
    //判断容量够不够
    if(p->objSize >= p->maxCap) {
        //new = Realloc(p->objects, sizeof(object_p)*2*p->max_cap); //扩大2倍
        oldP = p->objects;
        newP = Malloc(sizeof(LLRefPtr)*2 * p->maxCap);
        
        if(newP == NULL) {
            return NO;
        }
        for(i=0; i<p->objSize; i++) {
            realIndex = (p->headIndex+i)% p->maxCap;
            newP[i] = oldP[realIndex];
        }
        Free(oldP);
        p->objects = newP;
        p->headIndex = 0;
        p->tailIndex = p->objSize;
        p->maxCap *= 2;
        
    }
    return YES;
}

/*---------------------------------------------*\
 获取index上一个index
 \*---------------------------------------------*/

static uint LLArrayGetPreIndex(LLArray * const p, uint index)
{
    
    if(index == 0) {
        index = p->maxCap-1;
    }else{
        index--;
    }
    return  index;
}
/*---------------------------------------------*\
 获取index的后一个index
\*---------------------------------------------*/
static uint LLArrayGetNextIndex(LLArray * const p, uint index)
{
    
    if(index == p->maxCap-1) {
        index = 0;
    }else{
        index++;
    }
    return  index;
}
/*---------------------------------------------*\
 向左移动数据函数
\*---------------------------------------------*/
static void LLArrayForward( LLArray* const p, uint num, uint start)
{
    uint i,j;
    j = start;
    for(i = 0; i<num; i++,j++) {
        uint prej = LLArrayGetPreIndex(p, j);
        p->objects[prej] = p->objects[j];
    }
}

/*---------------------------------------------*\
 向右边移动数据函数
\*---------------------------------------------*/
static void LLArrayBackward( LLArray * const p, uint num ,uint end)
{
    uint i,j;
    j = end;
    for(i = 0; i<num; i++, j--) {
        uint nextj = LLArrayGetNextIndex(p, j);
        p->objects[nextj] = p->objects[j];
    }
    
}
static void LLArrayDealloc(void * const ptr)
{
    LLArray * pArray = (LLArray *) ptr;
    sint i;
    if(pArray->objects!=NULL) {
        //释放LLArray中的成员对象
        for(i=0; i<pArray->objSize; i++){
          
            LLRefPtr * obj = LLArrayGetObjectAt(pArray, i);
            LLRefRelease(obj);
            pArray->objects[i] = NULL;
        }
    }
}
