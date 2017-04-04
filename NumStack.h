//
//  Palindrome.h
//  newDataStructPro
//
//  Created by andybain on 27/03/2017.
//  Copyright © 2017 andybain. All rights reserved.
//

#ifndef NumStack_H
#define NumStack_H
#include "LLTypes.h"
typedef  struct{
    uint curSize;
    uint maxNum;
    sint * objects;
}NumStack;

NumStack * createStack(sint num);
BOOL stackPush(NumStack * ptr, sint value);
sint stackPop(NumStack * ptr);
BOOL stackClear(NumStack * ptr);
#endif /* Palindrome_h */
