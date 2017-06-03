#ifndef LJLINKLIST_H_
#define LJLINKLIST_H_
#include <stdio.h>
#include "LLTypes.h"
#include "LLRef.h"

typedef struct _LinkNode LinkNode;


typedef struct _LJLinkList
{
	LLRef  ref;
	uint   curSize;
    LinkNode * head;
}LJLinkList;

extern LJLinkList * LJLinkListCreate(void);
extern LLRefPtr     LJLinkListInit(LLRefPtr const ptr, DeallocFunc deallocFunPtr);
extern void LJLinkListDealloc(LLRefPtr const ptr);
#endif
