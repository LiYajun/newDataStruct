//
//  Palindrome.c
//  newDataStructPro
//
//  Created by andybain on 27/03/2017.
//  Copyright © 2017 andybain. All rights reserved.
//

#include "ArrayLikeLink.h"
#include "LLTypes.h"
#include "mem_allocator.h"
#define Init_Node_Num    20
#define AryNodeNull  -1
extern ArrayLikeLink* ArrayLikeLinkCreate(uint nodeNum)
{
	ArrayLikeLink * ptr = NULL;
	ptr = Malloc(sizeof(ArrayLikeLink));
	if (ptr == NULL) return NULL;
	uint num = nodeNum;
	if (num == 0) {
		num = Init_Node_Num;
	}
	
	ptr->linkAry = Calloc(num, sizeof(AryNode));
	ptr->nodeNum = num;
	for (uint i = 0; i < ptr->nodeNum; i++) {
		ptr->linkAry[i].next = AryNodeNull;
	}
}
extern BOOL ArrayLikeLinkInsert(ArrayLikeLink * ptr, sint value)
{
	AryNode node = ptr->linkAry[0];
	if (node.next = AryNodeNull)
	{
		ptr->linkAry[0].next = 0;
		ptr->linkAry[0].value = value;
	}
}
extern BOOL ArrayLikeLinkDel(ArrayLikeLink * ptr)
{

}




























