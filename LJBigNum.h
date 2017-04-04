#ifndef _LJBigNum_H_
#define _LJBigNum_H_
#include "LLTypes.h"
#include "LLRef.h"


typedef struct _LJBigNum{
	LLRef ref;
	uint  maxCap;
	uint  curSize;  //how many   
	uint8 * values;
	uint8 sign;     // 0 is  positive number, other is negative number
	uint  dotPos;   // 0 is not decimal (number) 
}LJBigNum;

extern LJBigNum * LJBigNumCreateBy(uint cap);
extern void		  LJBigNumAddOther(LJBigNum * ptr, LJBigNum * otherBigNum);
extern void       LJBigNumMinusOther(LJBigNum * ptr, LJBigNum * otherBigNum);
extern void		  LJBigNumDealloc(LLRefPtr const ptr);

#endif // 


