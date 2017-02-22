#include "LJHashTable.h"
#include "mem_allocator.h"
#define Hash_INIT_CAP   1007
static void LJHashTableDealloc(LLRefPtr const ptr);
static uint NextPrime(uint size);

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
		p->bucketsSize = NextPrime(Hash_INIT_CAP);
		p->buckets = (LLRefPtr*)Malloc(sizeof(LLRefPtr) * p->bucketsSize);
	}
	return p;
}
extern void LJHashTableDealloc(LLRefPtr const ptr)
{

}
/*比 size 大的素数*/
static uint NextPrime(uint size)
{
	return 1007;
}
