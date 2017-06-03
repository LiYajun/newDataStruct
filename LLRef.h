#ifndef _LLREF_H_
#define _LLREF_H_


#include "LLTypes.h"


typedef void  * LLRefPtr;
/************************************************************************\
 函数指针
\************************************************************************/
typedef void(*DeallocFunc)(LLRefPtr pRef);

typedef void(*DisplayFunc)(LLRefPtr pRef);


typedef struct _LLRef
{
	sint  retainCount;
    DeallocFunc dealloc;
}LLRef;

extern  LLRef *     LLRefCreate(void);
extern  LLRefPtr    LLRefInit(LLRefPtr ptr, DeallocFunc dallocFunPtr);
extern  sint        LLRefRelease(LLRefPtr ptr);
extern  sint        LLRefRetain(LLRefPtr  ptr);
extern  void        LLRefDealloc(LLRefPtr ptr);
extern  void        LLRefPrint(LLRefPtr ptr);

#endif // !_LLREF_H_


