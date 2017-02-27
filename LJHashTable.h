#ifndef LJHashTable_H
#define LJHashTable_H
#include <stdio.h>
#include "LLTypes.h"
#include "LLRef.h"
/*链式散列表*/
typedef struct _LJHashTable
{

	LLRef		ref;
	uint        bucketsSize;    /* 桶个数 */
	uint		objSize;		/* 现在的元素个数 */
	LLRefPtr  * buckets;        /* 桶数组 */
	 
}LJHashTable;
extern LJHashTable * LJHashTableCreate(void);
extern LLRefPtr LJHashTableInit(LLRefPtr const ptr, DeallocFunc deallocFunPtr);
#endif 
