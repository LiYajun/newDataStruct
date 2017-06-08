#include "LJLinkList.h"
#include "mem_allocator.h"

typedef struct _LinkNode{
    LLRefPtr   obj;
    LinkNode * next;
   // LinkNode * pre;
}LinkNode;

static void LJLinkListInsertAtHead(LJLinkList * const p, LinkNode * node);

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
        p->objSize = 0;
    }
    return p;
}
extern BOOL LJLinkListAddObj(LJLinkList * const p, LLRefPtr obj)
{
    assert(obj!=NULL);
    LinkNode * node = Malloc(sizeof(LinkNode));
    if(node == NULL){
    	return NO;
    }
    node->obj = obj;
    LLRefRetain(obj);	
    LJLinkListInsertAtHead(p, node);
    return YES;
}
static void LJLinkListInsertAtHead(LJLinkList * const p, LinkNode * node)
{
    LJLinkList * ptr = (LJLinkList*)p;

    if(p->head==NULL) {
        ptr->head = node;
    }else {
    	LinkNode * temp = ptr->head;
    	node->next = temp;
    	ptr->head = node;
    }

}
extern void LJLinkListDealloc(LLRefPtr const ptr)
{

}
