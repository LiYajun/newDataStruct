#ifndef _LJBigNum_H_
#define _LJBigNum_H_
#include "LLTypes.h"
#include "LLRef.h"

typedef enum {
	Sign_None = 0,
	Sign_Positive = 1,
	Sign_negative = -1
}BigNumSign;
typedef enum {
	Order_None = 0,
	Order_Big = 1,
	Order_Small = 2,
	Order_Same = 3,
}BigNumOrder;
typedef struct _LJBigNum{
	LLRef ref;
	uint  maxCap;
	uint  curSize;  //how many   
	int8 * values;
	BigNumSign sign;     // 1 is  positive number, -1 is negative number
	uint  dotPos;   // 0 is not decimal (number) 
}LJBigNum;

extern LJBigNum * LJBigNumCreateBy(uint cap);
extern LJBigNum * LJBigNumCreteByStr(const char * str);
extern void		  LJBigNumAddOther(LJBigNum * ptr, LJBigNum * otherBigNum);
extern void       LJBigNumMinusOther(LJBigNum * ptr, LJBigNum * otherBigNum);
extern void		  LJBigNumDealloc(LLRefPtr const ptr);
extern void		  LJBigNumPrintValues(LJBigNum *ptr);
#endif // 


