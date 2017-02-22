#ifndef LJHashTable_H
#define LJHashTable_H
#include <stdio.h>
#include "LLTypes.h"
#include "LLRef.h"
/*---------------------------------------------*\
 分离链表式散列表
\*---------------------------------------------*/
typedef struct _LJHashTable
{
	LLRef		ref;
	uint        bucketsSize;
	LLRefPtr  * buckets;
}LJHashTable;

extern LJHashTable * LJHashTableCreate(void);
extern LLRefPtr LJHashTableInit(LLRefPtr const ptr, DeallocFunc deallocFunPtr);
#endif 
