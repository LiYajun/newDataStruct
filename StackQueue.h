#ifndef StackQueue_H
#define StackQueue_H
#include "LLTypes.h"
#include "Palindrome.h"

typedef struct
{
	NumStack* stackIn;
	NumStack* stackOut;
	uint      maxCap;
	uint      curSize;
}NumQueue;

NumQueue * createQueue(sint num);
BOOL appendTail(NumQueue * ptr, sint value);
sint deleteHead(NumQueue * ptr);
void QueueClear(NumQueue * ptr);
#endif