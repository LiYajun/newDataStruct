#include "LJHashTable.h"
#include "mem_allocator.h"

#define HASH_INIT_CAP   1007
typedef struct _HashNode{
	LLRefPtr object;
	char *  key;
	struct _HashNode * next;
}HashNode;
typedef struct  _BucketNode {
	uint  hashNodeNum;
	HashNode * next;
}BucketNode;

static void LJHashTableDealloc(LLRefPtr const ptr);
static uint getPrimeNumBy(uint size);
static uint LJHashTableHash(LJHashTable * ptr, const char * key);

extern LJHashTable * LJHashTableCreate(void)
{
	LJHashTable * p = NULL;
	p = (LJHashTable*)Malloc(sizeof(LJHashTable));
	if (p == NULL) {
		return NULL;
	}
	return LJHashTableInit(p, LJHashTableDealloc);
}
extern LLRefPtr LJHashTableInitWithSize(LLRefPtr const ptr, uint size)
{
	LJHashTable * p = LLRefInit(ptr, LJHashTableDealloc);
	if (p != NULL) { 
		p->bucketsSize = getPrimeNumBy(size);  // get a prime number close to size, prime number >size
		p->buckets = (LLRefPtr*)Calloc(p->bucketsSize, sizeof(BucketNode));
		if (p->buckets == NULL) {
			Free(p);
			return NULL;
		}
		p->objSize = 0;
	}
	return p;
}
extern LLRefPtr LJHashTableInit(LLRefPtr const ptr, DeallocFunc deallocFunPtr)
{
	LJHashTable * p = LLRefInit(ptr, deallocFunPtr);
	if (p != NULL) {
		p->bucketsSize = getPrimeNumBy(HASH_INIT_CAP);
		p->buckets = (LLRefPtr*)Calloc(p->bucketsSize, sizeof(BucketNode));
		if (p->buckets == NULL) {
			Free(p);
			return NULL;
		}
		p->objSize = 0;
	}
	return p;
}
extern BOOL LJHashTableInsert(LLRefPtr const ptr, LLRefPtr anObject, const char * key)
{
	uint length = strnlen(key, 0xFF); //key length <= 255
	LJHashTable * p = (LJHashTable*)ptr;
	uint index = LJHashTableHash(ptr, key);
	BucketNode * bucketNode = p->buckets[index];
	if (bucketNode->next == NULL) {
		bucketNode->next = Malloc(sizeof(HashNode));
		HashNode * node = bucketNode->next;
		node->key = Malloc(sizeof(char)*(length + 1));
		strncpy(node->key, key,length+1);
	}
	return YES;
}
extern void LJHashTableDealloc(LLRefPtr const ptr)
{
	printf("LJHashTableDealloc called\n");

	LLRefDealloc(ptr);
	LJHashTable* pHashTable = (LJHashTable *)ptr;
	
	 
}
 
static uint LJHashTableHash(LJHashTable * ptr, const char * key)
{
	uint hashVal = 0;
	while (*key != '\0') {
		hashVal = (hashVal << 5) + *key++;
	}
	return hashVal % ptr->bucketsSize;
}

static uint getPrimeNumBy(uint size)
{
	return 1699;
}

