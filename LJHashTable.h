#ifndef LJHashTable_H
#define LJHashTable_H
#include <stdio.h>
#include "LLTypes.h"
#include "LLRef.h"
/*��ʽɢ�б�*/
typedef struct _LJHashTable
{

	LLRef		ref;
	uint        bucketsSize;    /* Ͱ���� */
	uint		objSize;		/* ���ڵ�Ԫ�ظ��� */
	LLRefPtr  * buckets;        /* Ͱ���� */
	 
}LJHashTable;
extern LJHashTable * LJHashTableCreate(void);
extern LLRefPtr LJHashTableInit(LLRefPtr const ptr, DeallocFunc deallocFunPtr);
#endif 
