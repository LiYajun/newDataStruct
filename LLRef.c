#include "LLRef.h"

LLRef * LLRefCreate(void)
{
	LLRef * pRef = (LLRef*)malloc(sizeof(LLRef));
	if(pRef){
		LLRefInit(pRef);
	}
	return pRef;
}

void LLRefInit(void * ptr)
{
	LLRef * pRef = (LLRef*)ptr;
	pRef->retainCount = 1;
}
int LLRefRelease(void * ptr)
{
	LLRef * pRef = (LLRef*)ptr;
	if (pRef->retainCount>0) {
		pRef->retainCount--;
	}
	int count = pRef->retainCount;
	if (pRef->retainCount == 0) {
		free(pRef);
	}
	return count;
}
int LLRefRetain(void * ptr)
{
	LLRef * pRef = (LLRef*)ptr;
	pRef->retainCount++;
	return pRef->retainCount;
}