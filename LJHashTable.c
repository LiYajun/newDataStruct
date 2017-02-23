#include "LJHashTable.h"
#include "mem_allocator.h"

typedef struct _LinkNode{
	LLRefPtr object;
	struct _LinkNode * next;
}LinkNode;

static void LJHashTableDealloc(LLRefPtr const ptr);
static uint getPrimeNumBy(uint size);
extern LJHashTable * LJHashTableCreate(void)
{
	LJHashTable * p = NULL;
	p = (LJHashTable*)Malloc(sizeof(LJHashTable));
	if (p == NULL) {
		return NULL;
	}

	return LJHashTableInit(p, LJHashTableDealloc);
}
extern LLRefPtr LJHashTableInit(LLRefPtr const ptr, DeallocFunc deallocFunPtr)
{
	LJHashTable * p = LLRefInit(ptr, deallocFunPtr);
	if (p != NULL) {
		p->bucketsSize = getPrimeNumBy(107);
		p->buckets = (LLRefPtr*)Malloc(sizeof(LLRefPtr) * p->bucketsSize);
	}
	return p;
}
extern void LJHashTableDealloc(LLRefPtr const ptr)
{

}
static int LJHashTableHash(const char * key)
{

}
static uint getPrimeNumBy(uint size)
{
	return 1699;
}