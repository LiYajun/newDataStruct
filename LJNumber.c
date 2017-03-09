//
//  LLTArray.c
//  newDataStructPro
//
//  Created by li yajun on 17/1/9.
//  Copyright 2017 li yajun. All rights reserved.
//

#include "LJNumber.h"
#include "mem_allocator.h"
#include "LLRef.h"

static void LJNumberDealloc(LLRefPtr const p);
static LLRefPtr LJNumberInitWithNumber(LLRefPtr  ptr, sint m);
extern LJNumber * LJNumberCreateByNum(sint m)
{
	LJNumber * p = NULL;
	p = (LJNumber *)Malloc(sizeof(LJNumber));
	if (p == NULL)
		return NULL;
	return LJNumberInitWithNumber(p, m);
}


LLRefPtr LJNumberInitWithNumber(LLRefPtr ptr, sint m)
{
	LJNumber * p = LLRefInit(ptr, LJNumberDealloc);
	if (p != NULL) {
		p->val = m;
	}
	return p;
}
static void LJNumberDealloc(LLRefPtr const p)
{
    printf("%s called\n",__FUNCDNAME__);
}
