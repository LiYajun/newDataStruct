#include "LLRef.h"
#include "LJBigNum.h"
#include "mem_allocator.h"
#define  INIT_BIGNUM_CAP    100    

static LLRefPtr	    LJBigNumInitByCap(LJBigNum * ptr, uint cap);
static uint		 	LJBigNumCalcNewCurSize(LJBigNum * ptr);
static void			LJBigNumAbsValuesMinus(LJBigNum * ptr, LJBigNum * other);
static void		    LJBigNumAbsValuesAdd(LJBigNum * ptr, LJBigNum * other);
static BigNumOrder  LJBigNumAbsCompare(LJBigNum * ptr, LJBigNum * other);
static LLRefPtr		LJBigNumInitByStr(LJBigNum * ptr,const char * str);
static BOOL			LJBigNumSetNum(LJBigNum * ptr, const char * str, uint strSize);


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
extern LJBigNum * LJBigNumCreteByStr(const char * str)
{
	if (str == NULL) {
		return NULL;
	}
	LJBigNum * ptr = Malloc(sizeof(LJBigNum));
	if (ptr == NULL) return NULL;
	return LJBigNumInitByStr(ptr, str);
}
static LLRefPtr LJBigNumInitByStr(LJBigNum * ptr,  const char * str)
{
	uint i = 0;
	LJBigNum * p = (LJBigNum*)LLRefInit(ptr, LJBigNumDealloc);
	if (p != NULL) {
		uint size = StrLen(str);
		uint cap =  size + 10; // more than 
		p->values = Calloc(cap, sizeof(int8));
		if (p->values == NULL) {
			Free(p);
			return NULL;
		}
		p->maxCap = cap;
		LJBigNumSetNum(p, str, size);
	}
	return p;
}
static BOOL LJBigNumSetNum(LJBigNum * ptr, const char * str, uint strSize)
{
	if (ptr->maxCap < strSize) return NO;
	uint i = 0;
	for (; i < strSize; i++) {
		int8 val = str[strSize - i - 1] - '0';
		ptr->values[i] = val;
	}
	ptr->curSize = strSize;
	return YES;
}
static LLRefPtr LJBigNumInitByCap(LJBigNum * ptr, uint cap)
{
	LJBigNum * p = LLRefInit(ptr, LJBigNumDealloc);
	if (p != NULL) 
	{
		p->values = Calloc(cap, sizeof(int8));
		if (p->values == NULL) {
			Free(p);
			return NULL;
		}
		p->maxCap = cap;
		p->curSize = 0;
	}
	return p;
}
static BOOL LJBigNumCheckMaxCap(LJBigNum * ptr, uint needSize)
{
	 
	uint i;
	if (ptr->maxCap >= needSize)
		return YES;
	uint newSize = (uint)(1.414 * needSize);
	int8 * oldPtr = ptr->values;
	int8 * newPtr = Calloc(newSize, sizeof(int8));
	if (newPtr == NULL)
		return NO;
	for (i = 0; i < ptr->curSize; i++) {
		newPtr[i] = oldPtr[i];
	}
	ptr->values = newPtr;
	Free(oldPtr);
	return YES;
}
static void LJBigNumAbsValuesAdd(LJBigNum * ptr, LJBigNum * other)
{
	uint size = ptr->curSize > other->curSize ? ptr->curSize : other->curSize;

	if (LJBigNumCheckMaxCap(ptr, size + 1) == NO) {
		fprintf(stderr, "failed realloc memeory!");
		return;
	}

	int8 * selfValues  = ptr->values;
	int8 * otherValues = other->values;
	uint i =0;
	int8 isAdding = 0;
	int8 val = 0;
	for (i=0; i < size; i++) {
		val = selfValues[i] + otherValues[i] + isAdding;
		isAdding = val >= 10 ? 1 : 0;
		val = (isAdding == 1 ? val - 10 : val);
		selfValues[i] = val;
	} 
	if (isAdding == 1)
	{
		selfValues[i] = isAdding;
		ptr->curSize = size + 1;
	}
	else {
		ptr->curSize = size;
	}
	
}
extern void LJBigNumZero(LJBigNum * ptr)
{
	for (uint i = 0; i < ptr->curSize; i++) {
		ptr->values[i] = 0;
	}
}
static uint LJBigNumCalcNewCurSize(LJBigNum * ptr)
{
	sint i;
	uint newSize = 0;
	for ( i = ptr->curSize - 1; i >= 0; i--) {

		if (ptr->values[i] == 0)
			continue;
		else
			break;
	}
	newSize = i + 1;
	return newSize;
}
static void LJBigNumAbsValuesMinus(LJBigNum * ptr,  LJBigNum * other)
{
	uint size = ptr->curSize > other->curSize ? ptr->curSize : other->curSize;

	if (LJBigNumCheckMaxCap(ptr, size ) == NO) {
		fprintf(stderr, "failed realloc memeory!");
		return;
	}

	BigNumOrder order = LJBigNumAbsCompare(ptr, other);
	int8 * selfValues = NULL, *otherValues = NULL;
	BigNumSign sign = Sign_None;
	if (order == Order_Big) {
		selfValues = ptr->values;
		otherValues = other->values;
		sign = ptr->sign;
	}
	else if (order == Order_Small) {
		selfValues = other->values;
		otherValues = ptr->values;
		sign = other->sign;
	}
	else
	{
		sign = ptr->sign;
		LJBigNumZero(ptr);
        ptr->curSize = 1;
        ptr->sign = Sign_Positive;
		return;
	}
	uint i = 0;
	int8 isBorrow = 0;
	uint8 val = 0;
	for (i = 0; i < size; i++) {
		val = selfValues[i] - otherValues[i] + isBorrow;
		isBorrow = val < 0 ? -1 : 0;
		val = (isBorrow == -1 ? val + 10 : val);
		ptr->values[i] = val;
	}
    ptr->curSize = size;
    ptr->curSize = LJBigNumCalcNewCurSize(ptr);
	ptr->sign = sign;
}

//abs value compare
static BigNumOrder LJBigNumAbsCompare(LJBigNum * ptr, LJBigNum * other)
{
	if (ptr->curSize > other->curSize)
	{
		return Order_Big;
	}
	else if (ptr->curSize < other->curSize) 
	{
		return Order_Small;
	}
	else
	{
		uint len = ptr->curSize;
		sint i;
	
		for (i = len - 1; i >= 0; i--) {
			if (ptr->values[i] > other->values[i]) {
					
				return Order_Big;
			}
			else if (ptr->values[i] < other->values[i]) {
						
				return Order_Small;
			}
			else {
				continue;
			}
		}
		return Order_Same;
	}
}
extern void LJBigNumAddOther(LJBigNum * ptr, LJBigNum * other)
{
	if(ptr->sign == other->sign){
		LJBigNumAbsValuesAdd(ptr, other);
	}
	else
	{
		LJBigNumAbsValuesMinus(ptr, other);
	}
}

extern void LJBigNumMinusOther(LJBigNum * ptr, LJBigNum * otherBigNum)
{

}
extern void	LJBigNumDealloc(LLRefPtr  ptr)
{
	printf("LJBigNumDealloc called\n");
	LJBigNum * bigNum = (LJBigNum *)ptr;
	if (bigNum->values != NULL) {	
		Free( bigNum->values );
	}
	LLRefDealloc(ptr);
}

extern void LJBigNumPrintValues(LJBigNum *ptr)
{
	char * str = Malloc(sizeof(char) *ptr->curSize + 1);
	for (int i = 0; i < ptr->curSize; i++)
		printf("%d", ptr->values[ptr->curSize - i - 1]);
    for(uint i=0; i<ptr->curSize; i++){
        str[i] = ptr->values[ptr->curSize - i -1] +'0';
    }
	str[ptr->curSize] ='\0';
    if(ptr->sign == Sign_Positive)
        fprintf(stdout, "\nbigNum:%s", str);
    else if(ptr->sign == Sign_negative)
        fprintf(stdout, "\nbigNum:-%s", str);
	Free(str);
}
