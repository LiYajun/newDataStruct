#include "LJLinkList.h"
#include "mem_allocator.h"
#include <assert.h>

typedef struct _LinkNode{
    LLRefPtr   obj;
    LinkNode * next;
   // LinkNode * pre;
}LinkNode;

static void LJLinkListInsertAtHead(LJLinkList * const p, LinkNode * node);
static LinkNode * LinkNodeCreate();

static LinkNode * LinkNodeCreate()
{
    LinkNode * node = Malloc(sizeof(LinkNode));
    if(node !=NULL)
        node->next = node->obj = NULL;
    
    return node;
}
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
    LinkNode * node = LinkNodeCreate();
    if(node == NULL){
    	return NO;
    }
    node->obj = obj;
    LLRefRetain(obj);
    //insert at head position
    LJLinkListInsertAtHead(p, node);
    p->objSize++;
    return YES;
}
extern LLRefPtr LJLinkListGetHeadObj(LJLinkList * const p)
{
    LinkNode * node = p->head;
    if(node == NULL)
        return NULL;
    else
        return node->obj;
}
extern void LJLinkListDealloc(LLRefPtr const p)
{
    printf("LJLinkListDealloc called\n");
    LJLinkList * ptr = (LJLinkList*)p;
    LinkNode * cur_node = ptr->head;
    
    while (cur_node!=NULL) {
        LinkNode * temp = cur_node->next;
        LLRefRelease(cur_node->obj);
        Free(cur_node);
        cur_node = temp;
    }
    ptr->head = NULL;
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




































