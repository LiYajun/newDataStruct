//
//  Palindrome.c
//  newDataStructPro
//
//  Created by andybain on 27/03/2017.
//  Copyright © 2017 andybain. All rights reserved.
//

#include "Palindrome.h"
#include "LLTypes.h"
#include "mem_allocator.h"

typedef  struct{
    uint num;
    uint maxNum;
    sint * objects;
}NumStack;
NumStack * createStack(sint num)
{
    NumStack * ptr = Malloc(sizeof(NumStack));
    
    if(ptr == NULL) return NULL;
    
    ptr->objects = Malloc(sizeof(sint) * num);
    if(ptr->objects == NULL) return NULL;
    ptr->num = 0;
    ptr->maxNum = num;
    return ptr;
}
BOOL stackPush(NumStack * ptr, sint value)
{
    if(ptr ==NULL) return NO;
    if(ptr->num >= ptr->maxNum) return  NO;
    
    ptr->objects[ptr->num] = value;
    ptr->num++;
    return YES;
}
sint stackPop(NumStack * ptr)
{
    sint value = INT32_MAX;
    
    if(ptr ==NULL)
        return INT32_MAX;
    if(ptr->num == 0) return INT32_MAX;
    
    value = ptr->objects[ptr->num-1];
    ptr->num--;
    return value;
    
}
BOOL stackClear(NumStack * ptr)
{
    if(ptr == NULL) return NO;
    ptr->num = 0;
    return  YES;
}
BOOL isPalindrome(const char * str)
{
    uint i;
	BOOL flag = YES;
    ulong len = StrLen(str);
	
    NumStack * stack = createStack(100);
    for(i =0; i<len; i++)
        stackPush(stack, str[i]);

	for (i = 0; i < len; i++)
	{
		char val1 = str[ i ];
		char val2 = stackPop(stack);
		if (val1 != val2) {
			flag = NO;
			break;
		}
	}
	
    return  flag;
}

typedef struct
{

	NumStack* stackIn;
	NumStack* stackOut;
}NumQueue;

NumQueue * createQueue(sint num)
{
	NumQueue * ptr = Malloc(sizeof(NumQueue));
	ptr->stackIn = createStack(num / 2);
	ptr->stackOut = createStack(num / 2);
	return  ptr;
}

BOOL appendTail(NumQueue * ptr, sint value)
{
	if (ptr->stackOut->num > 0)
	{

	}
	BOOL flag = stackPush(ptr->stackIn, value);
	return flag;
}
 




























