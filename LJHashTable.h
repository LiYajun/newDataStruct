#ifndef LJHashTable_H
#define LJHashTable_H
#include <stdio.h>
#include "LLTypes.h"
#include "LLRef.h"
typedef struct _HashNode	HashNode;
typedef struct _BucketNode  BucketNode;
/*Á´Ê½É¢ÁÐ±í*/
typedef struct _LJHashTable
{
	LLRef		ref;
	uint        bucketsSize;    /* bucket size*/
	uint		objSize;		/* element size */
	BucketNode * buckets;        /*bucket  */ 
}LJHashTable;
extern LJHashTable * LJHashTableCreate(void);
extern LLRefPtr		 LJHashTableInit(LLRefPtr const ptr, DeallocFunc deallocFunPtr);
extern BOOL			 LJHashTableInsert(LJHashTable * const ptr, LLRefPtr anObject, const char * key);
extern LLRefPtr		 LJHashTableObjectForKey(LJHashTable * const ptr, const char *  key);
extern void			 LJHashTableRemoveObjectForKey(LJHashTable * const ptr, const char *  key);
#endif 
