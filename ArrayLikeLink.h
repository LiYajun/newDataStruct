//
//  Palindrome.h
//  newDataStructPro
//
//  Created by andybain on 27/03/2017.
//  Copyright © 2017 andybain. All rights reserved.
//

#ifndef ArrayLikeLink_H
#define ArrayLikeLink_H
#include "LLTypes.h"
 
typedef struct
{
	uint value;
	uint next;
}AryNode;
typedef struct 
{
	uint nodeNum;
	AryNode * linkAry;
}ArrayLikeLink;

extern ArrayLikeLinkCreate(uint nodeNum);
#endif /* Palindrome_h */
