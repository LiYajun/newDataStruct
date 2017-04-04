#include "LLRef.h"
#include "LJBigNum.h"
#include "mem_allocator.h"
#define  INIT_BIGNUM_CAP    100    
static LLRefPtr LJBigNumInitByCap(LJBigNum * ptr, uint cap);
extern LJBigNum * LJBigNumCreateBy(uint cap)
{
	if (cap <= 0)
	{
		cap = INIT_BIGNUM_CAP;
	}
	LJBigNum * ptr = Malloc(sizeof(LJBigNum));
	if (ptr == NULL) return NULL;
	return LJBigNumInitByCap(ptr, cap);
}
static LLRefPtr LJBigNumInitByCap(LJBigNum * ptr, uint cap)
{
	LJBigNum * p = LLRefInit(ptr, LJBigNumDealloc);
	if (p != NULL) 
	{
		p->values = Calloc(cap, sizeof(uint8));
		if (p->values == NULL) {
			Free(p);
			return NULL;
		}
		p->maxCap = cap;
		p->curSize = 0;
	}
	return p;
}
static void LJBigNumValuesAdd(uint * selfValues, uint * otherValues, uint size)
{
	uint i=0;
	uint8 isAdding = 0;
	uint val = 0;
	for (; i < size; i++) {
		val = selfValues[i] + otherValues[i] + isAdding;
		isAdding = val / 10;
		val = (isAdding == 1 ? val % 10 : val);
		selfValues[i] = val;
	} 
}
extern void LJBigNumAddOther(LJBigNum * ptr, LJBigNum * otherBigNum)
{
	uint i;
	uint selfLen = ptr->curSize;
	uint otherLen = ptr->curSize;
	
}

extern void LJBigNumMinusOther(LJBigNum * ptr, LJBigNum * otherBigNum)
{

}
extern void	LJBigNumDealloc(LLRefPtr const ptr)
{

}
