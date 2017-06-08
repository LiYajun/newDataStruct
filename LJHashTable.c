#include "LJHashTable.h"
#include "mem_allocator.h"
#include "LLRef.h"

#define HASH_INIT_CAP   1007

typedef struct _HashNode{
	LLRefPtr object;
	char *  key;
	HashNode * next;
}HashNode;
typedef struct  _BucketNode {
	uint  hashNodeNum;
	HashNode * next;
}BucketNode;

extern void LJHashTableDealloc(LLRefPtr const ptr);
static uint getPrimeNumBy(uint min);
static uint LJHashTableHash(LJHashTable * ptr, const char * key);
static void LJHashTableReleaseBucket(BucketNode * bucketNode);
static BOOL LJHashTableEqual(const char *key1, const  char *key2);
static BOOL isPrime(uint num);
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
		p->buckets = (BucketNode*)Calloc(p->bucketsSize, sizeof(BucketNode));
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
		p->buckets = (BucketNode*)Calloc(p->bucketsSize, sizeof(BucketNode));
		if (p->buckets == NULL) {
			Free(p);
			return NULL;
		}
		p->objSize = 0;
	}
	return p;
}
//linked hash talbe always can insert
extern BOOL LJHashTableInsert(LJHashTable * const ptr, LLRefPtr anObject, const char * key)
{
	uint length = StrnLen(key, 0xFF); //key length <= 255
	LJHashTable * p = (LJHashTable*)ptr;
	uint index = LJHashTableHash(ptr, key);
	BucketNode *  bucketNode = &p->buckets[index];
	HashNode * node = bucketNode->next;
    //already element here
	while (node != NULL) {
		if ( LJHashTableEqual(node->key, key) == YES) { //keys are same
				LLRefRelease(node->object);
				node->object = anObject;
				LLRefRetain(anObject);
				//p->objSize++;
				return  YES ;
		}
		node = node->next;
	}
	//head insert
	node = Malloc(sizeof(HashNode));
	if (node == NULL) return NO;
	node->key = Malloc(sizeof(char)*(length + 1));
	if (node->key == NULL) {
		Free(node);
		return NO;
	}
	StrnCpy(node->key, key, length + 1);
	node->object = anObject;
	LLRefRetain(anObject);
	p->objSize++;
	HashNode * firstNode = bucketNode->next;
	bucketNode->next = node;
	node->next = firstNode;
	return  YES;
}
extern LLRefPtr LJHashTableObjectForKey(LJHashTable * const ptr, const char *  key)
{
	LJHashTable * p = (LJHashTable*)ptr;
	uint index = LJHashTableHash(p, key);
	BucketNode *  bucketNode = &p->buckets[index];
	HashNode * node = bucketNode->next;
	while (node != NULL) {
		if (LJHashTableEqual(node->key, key) == YES) {
			return node->object;
		}
		node = node->next;
	}
	return NULL;
}
extern void LJHashTableRemoveObjectForKey(LJHashTable * const ptr, const char *  key)
{
	LJHashTable * p = (LJHashTable*)ptr;
	uint index = LJHashTableHash(p, key);
	BucketNode * bucketNode = &p->buckets[index];
	HashNode * node = bucketNode->next;

	if (node == NULL) return ;
	int i = 0;
	HashNode * preNode = node;
	while(node != NULL){
		if (StrnCmp(node->key, key, 0xFF) == 0) {
			LLRefRelease(node->object);
			if (i == 0) {
				bucketNode->next = node->next;
				Free(node);
			}else {
				preNode->next = node->next;
				Free(node);
			}
			p->objSize--;
			return;
		}
		i++;
		preNode = node;
		node = node->next;
	}
}
extern void LJHashTableDealloc(LLRefPtr const ptr)
{
	printf("LJHashTableDealloc called\n");
	LJHashTable* p  = (LJHashTable *)ptr;
	//clear memory
	for (uint i = 0; i < p->bucketsSize; i++) {
		BucketNode * bucket = &p->buckets[i];
		LJHashTableReleaseBucket(bucket);
	}
	Free(p->buckets);
	LLRefDealloc(ptr);

}
static void LJHashTableReleaseBucket(BucketNode * bucketNode)
{
	HashNode * node = bucketNode->next;
	HashNode * preNode = node;
	while (node != NULL) {
		LLRefRelease(node->object);
		Free(node->key);
		node = node->next;
		Free(preNode);
		preNode = node;
	}
}
static BOOL LJHashTableEqual(const char * key1, const char * key2)
{
	return  StrnCmp(key1, key2, 0xFF) == 0 ? YES : NO;
}
 // key in "a,b,c...z" or "A,B,C...Z"
static uint LJHashTableHash(LJHashTable * ptr, const char * key)
{
	uint hashVal = 0;
	while (*key != '\0') {
		hashVal = (hashVal << 5) + *key++;
	}
	return hashVal % ptr->bucketsSize;
}
static uint getPrimeNumBy(uint min)
{
	for (int num = min;  ;num++) {
		if (isPrime(num) == YES) {
			return num;
		}
	}
}

static BOOL isPrime(uint num) {
	for (uint j = 2; j * j <= num; j++) {
		if (num % j == 0) {
			return NO;
		}
	}
	return YES;
}

