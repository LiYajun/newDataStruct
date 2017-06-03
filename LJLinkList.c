#include "LJLinkList.h"
#include "mem_allocator.h"

typedef struct _LinkNode{
    LLRefPtr   obj;
    LinkNode * next;
}LinkNode;

extern LJLinkList * LJLinkListCreate(void)
{
	LJLinkList * p = NULL;
	p = (LJLinkList*)Malloc(sizeof(LJLinkList));
	if (p == NULL) {
		return NULL;
	}
	return LJLinkListInit(p, LJLinkListDealloc);
}
extern LLRefPtr LJLinkListInit(LLRefPtr const ptr, DeallocFunc deallocFunPtr)
{
    LJLinkList * p = LLRefInit(ptr, deallocFunPtr);
    if(p!=NULL){
        p->head = NULL;
        p->curSize = 0;
    }
    return p;
}
extern void LJLinkListDealloc(LLRefPtr const ptr)
{

}
