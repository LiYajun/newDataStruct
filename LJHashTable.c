#include "LJHashTable.h"
#include "mem_allocator.h"
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
		p->bucketsSize = NextPrime(107);
		p->buckets = (LLRefPtr*)Malloc(sizeof(LLRefPtr) * 1007);
	}
	return p;
}
void LJHashTableDealloc(LLRefPtr const ptr)
{

}
/*比 size 大的素数*/
static uint NextPrime(uint size)
{
	return 1007;
}