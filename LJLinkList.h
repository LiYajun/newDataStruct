#ifndef LJLINKLIST_H_
#define LJLINKLIST_H_
#include <stdio.h>
#include "LLTypes.h"
#include "LLRef.h"

typedef struct _LinkNode LinkNode;


typedef struct _LJLinkList
{
	LLRef  ref;
	uint   objSize;
    LinkNode * head;
}LJLinkList;

extern LJLinkList * LJLinkListCreate(void);
extern LLRefPtr     LJLinkListInit(LLRefPtr const ptr, DeallocFunc deallocFunPtr);
extern void LJLinkListInsertAtHead(LJLinkList * const p, LinkNode * node);
extern void LJLinkListDealloc(LLRefPtr const ptr);
#endif
