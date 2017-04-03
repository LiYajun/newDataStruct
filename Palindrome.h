//
//  Palindrome.h
//  newDataStructPro
//
//  Created by andybain on 27/03/2017.
//  Copyright © 2017 andybain. All rights reserved.
//

#ifndef Palindrome_h
#define Palindrome_h
#include "LLTypes.h"
typedef  struct{
    uint curSize;
    uint maxNum;
    sint * objects;
}NumStack;
BOOL isPalindrome(const char * str);
BOOL stackPush(NumStack * ptr, sint value);
sint stackPop(NumStack * ptr);
BOOL stackClear(NumStack * ptr);
#endif /* Palindrome_h */
