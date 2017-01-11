#ifndef _LLREF_H_
#define _LLREF_H_


#include "LLTypes.h"


typedef struct _LLRef
{
	sint  retainCount;
    void  (*dealloc)(void * pRef);
}LLRef;


typedef void  (*deallocFun)(void * pRef);
typedef void  * LLRefPtr;


extern  LLRef * LLRefCreate(void);
extern  void  * LLRefInit(void * ptr, deallocFun dallocFunPtr);
extern  sint    LLRefRelease(void * ptr);
extern  sint    LLRefRetain(void * ptr);
extern  void    LLRefDealloc(void * ptr);


#endif // !_LLREF_H_


