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

static LLRefPtr LLArrayInitByCap(LLArray * const p, uint initCap);


static BOOL LLArrayCheckMaxCap(LLArray* const p);

static void LLArrayForward(LLArray* const p, uint num, uint start);
static void LLArrayBackward(LLArray * const p, uint num, uint end);

static uint LLArrayGetPreIndex(LLArray * const p, uint index);
static uint LLArrayGetNextIndex(LLArray * const p, uint index);

static void LLArrayPrint(LLRefPtr ptr);

extern LLArray * LLArrayCreate(void)
{
	return LLArrayCreateByCap(INIT_CAP);
}
extern LLArray * LLArrayCreateByCap(sint initCap)
{
	LLArray* p = NULL;

	if (initCap <= 0) {
		initCap = INIT_CAP;
	}

	p = (LLArray*)Malloc(sizeof(LLArray));

	if (p == NULL) {
		return NULL;
	}

	return  LLArrayInitByCap(p, initCap);


}
/*---------------------------------------------*\
 初始化
\*---------------------------------------------*/

extern LLRefPtr LLArrayInit(LLRefPtr const ptr, DeallocFunc deallocFunPtr)
{
	LLArray * p = LLRefInit(ptr, deallocFunPtr);
	if (p != NULL) {
		p->objects = NULL;
		p->objects = (LLRefPtr*)Malloc(sizeof(LLRefPtr) * INIT_CAP);

		if (p->objects == NULL) {
			Free(p);
			return NULL;
		}
		p->maxCap = INIT_CAP;
		p->objSize = 0;
		p->headIndex = 0;
		p->tailNextIndex = p->objSize;
        ((LLRef*)p)->display = NULL;
        ((LLRef*)p)->display = LLArrayPrint;
	}
	return p;
}

static LLRefPtr LLArrayInitByCap(LLArray * const ptr, uint initCap)
{
	LLArray * p = LLRefInit(ptr, LLArrayDealloc);
	if (p != NULL) {
		p->objects = NULL;
		p->objects = (LLRefPtr*)Malloc(sizeof(LLRefPtr) * initCap);

		if (p->objects == NULL) {
			Free(p);
			return NULL;
		}
		p->maxCap = initCap;
		p->objSize = 0;
		p->headIndex = 0;
		p->tailNextIndex = p->objSize;
	}
	return  p;
}

extern void LLArrayAddObject(LLArray* const p, LLRefPtr anObjct)
{
	LLArrayInsertAt(p, anObjct, p->objSize);
}
/*---------------------------------------------*\
 插入一个元素
\*---------------------------------------------*/
extern void LLArrayInsertAt(LLArray * const p, LLRefPtr anObject, uint index)
{
	uint realIndex = 0;
	LLRef * object = anObject;

	assert(anObject != NULL);

	if (index > p->objSize) {
		fprintf(stderr, "index out of array range!");
		return;
	}
	if (LLArrayCheckMaxCap(p) == NO) {
		fprintf(stderr, "failed realloc memory!");
		return;
	}

	//获取实际的插入位置
	realIndex = (p->headIndex + index) % p->maxCap;

	if (index < (p->objSize + 1) / 2) {
		realIndex = LLArrayGetPreIndex(p, realIndex); //实际的位置
		LLArrayForward(p, index, p->headIndex);
		p->objects[realIndex] = object;
		p->headIndex = LLArrayGetPreIndex(p, p->headIndex);
	}
	else {
		uint tailIndex = LLArrayGetPreIndex(p, p->tailNextIndex);
		LLArrayBackward(p, p->objSize - index, tailIndex);
		p->objects[realIndex] = object;
		p->tailNextIndex = LLArrayGetNextIndex(p, p->tailNextIndex);
	}
	LLRefRetain(object);

	p->objSize++;
}
/*---------------------------------------------*\
 移除一个对象
\*---------------------------------------------*/
extern BOOL LLArrayRemoveAt(LLArray * const p, uint index)
{
	uint realIndex = 0;
	LLRefPtr obj = NULL;
	//assert(p != NULL);

	if (index >= p->objSize) {
		fprintf(stderr, "index out of array range! del index form 0  to objsize -1!");
		return NO;
	}
	realIndex = (p->headIndex + index) % p->maxCap;
	obj = p->objects[realIndex];
	if (index < (p->objSize + 1) / 2) { //删除的元素在前半段，
		realIndex = LLArrayGetPreIndex(p, realIndex);
		LLArrayBackward(p, index, realIndex);
		p->headIndex = LLArrayGetNextIndex(p, p->headIndex);
	}
	else {
		realIndex = LLArrayGetNextIndex(p, realIndex);
		LLArrayForward(p, p->objSize - index - 1, realIndex);
		p->tailNextIndex = LLArrayGetPreIndex(p, p->tailNextIndex);
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
	uint realIndex = 0;

	if (index >= p->objSize) {
		fprintf(stderr, "index out of array range! del index form 0 ~ objsize -1!");
		return NULL;
	}
	realIndex = (p->headIndex + index) % p->maxCap;
	return    p->objects[realIndex];
}

/*---------------------------------------------*\
 检查容量
\*---------------------------------------------*/
static BOOL LLArrayCheckMaxCap(LLArray* const p)
{
	LLRefPtr * newP = NULL;
	LLRefPtr * oldP = NULL;
	uint realIndex = 0;
	uint i;
	//判断容量够不够
	if (p->objSize >= p->maxCap) {
		//new = Realloc(p->objects, sizeof(object_p)*2*p->max_cap); //扩大2倍
		oldP = p->objects;
		newP = Malloc(sizeof(LLRefPtr) * 2 * p->maxCap);

		if (newP == NULL) {
			return NO;
		}
		for (i = 0; i < p->objSize; i++) {
			realIndex = (p->headIndex + i) % p->maxCap;
			newP[i] = oldP[realIndex];
		}
		Free(oldP);
		p->objects = newP;
		p->headIndex = 0;

		p->tailNextIndex = p->objSize;
		p->maxCap *= 2;

	}
	return YES;
}

/*---------------------------------------------*\
 获取index上一个index
 \*---------------------------------------------*/

static uint LLArrayGetPreIndex(LLArray * const p, uint index)
{

	if (index == 0) {
		index = p->maxCap - 1;
	}
	else {
		index--;
	}
	return  index;
}
/*---------------------------------------------*\
 获取index的后一个index
\*---------------------------------------------*/
static uint LLArrayGetNextIndex(LLArray * const p, uint index)
{

	if (index == p->maxCap - 1) {
		index = 0;
	}
	else {
		index++;
	}
	return  index;
}
/*---------------------------------------------*\
 向左移动数据函数
 num: 需要移动的数据个数
 start: 左边第一个的数据的下标
\*---------------------------------------------*/
static void LLArrayForward(LLArray* const p, uint num, uint start)
{
	uint i, j;
	j = start;
	for (i = 0; num > 0 && i < num; i++, j++) {
		uint prej = LLArrayGetPreIndex(p, j);
		p->objects[prej] = p->objects[j];
	}
}

/*---------------------------------------------*\
 向右边移动数据函数
 num: 需要移动的数据个数
 end: 右边最后一个数据的下标
\*---------------------------------------------*/
static void LLArrayBackward(LLArray * const p, uint num, uint end)
{
	uint i, j;
	j = end;
	for (i = 0; num > 0 && i < num; i++, j--) {
		uint nextj = LLArrayGetNextIndex(p, j);
		p->objects[nextj] = p->objects[j];
	}

}
extern void LLArrayDealloc(LLRefPtr const ptr)
{
	printf("LLArrayDealloc called\n");

	LLRefDealloc(ptr);
	LLArray * pArray = (LLArray *)ptr;
	sint i;
	if (pArray->objects != NULL) {
		//释放LLArray中的成员对象
		for (i = 0; i < pArray->objSize; i++) {

			LLRefPtr * obj = LLArrayGetObjectAt(pArray, i);
			LLRefRelease(obj);
			pArray->objects[i] = NULL;
		}
        Free(pArray->objects);
	}
}
static void LLArrayPrint(LLRefPtr ptr)
{
    LLArray * p = (LLArray*) ptr;
    
    fprintf(stdout,
            "print values of LLArray:\n"
            "objSize:         %d\n"
            "headIndex:       %d\n"
            "tailNextIndex:   %d\n",
            p->objSize,
            p->headIndex,
            p->tailNextIndex );
}

















