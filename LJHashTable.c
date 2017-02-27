#include "LJHashTable.h"
#include "mem_allocator.h"

#define Hash_INIT_CAP   1007
typedef struct _HashNode{
	LLRefPtr object;
	char *  key;
	struct _HashNode * next;
}HashNode;
typedef struct  _HashHead {
	uint  hashNodeNum;
	HashNode * next;
}HashHead;

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
		p->bucketsSize = getPrimeNumBy(Hash_INIT_CAP);
		p->buckets = (LLRefPtr*)Calloc(p->bucketsSize, sizeof(LLRefPtr));
		if (p->buckets == NULL) {
			Free(p);
			return NULL;
		}
		p->objSize = 0;
	}
	return p;
}

static uint LJHashTableHash(LJHashTable * ptr, const char * key)
{
	uint hashVal = 0;
	while (*key != '\0') {
		hashVal = (hashVal << 5) + *key++;
	}
	return hashVal % ptr->bucketsSize;
}
extern void LJHashTableDealloc(LLRefPtr const ptr)
{

}

static uint getPrimeNumBy(uint size)
{
	return 1699;
}

