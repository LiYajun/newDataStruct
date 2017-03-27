#ifndef LJStack_H
#define LJStack_H
#include "LLTypes.h"
#include "LLRef.h"
#include "LLArray.h"
typedef  LLArray LJStack;


extern LJStack * LJStackCreateByCap(sint cap);

extern void  LJStackPush(LJStack * p, LLRefPtr obj);

extern LLRefPtr LJStackPop(LJStack * p);


#endif
