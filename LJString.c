//
//  LLTArray.c
//  newDataStructPro
//
//  Created by li yajun on 17/1/9.
//  Copyright 2017 li yajun. All rights reserved.
//

#include "LJString.h"
#include "mem_allocator.h"
#include "LLRef.h"

static void LJStringDealloc(void * const p);

LJString * LJStringCreateByString(const char * str)
{
	LJString * p = NULL;
	p = (LJString*)Malloc(sizeof(LJString));
	if (p == NULL)
		return NULL;
	return LJStringInitByString(p, str);
}


LLRefPtr LJStringInitByString(LLRefPtr const ptr, const char * str)
{
	LJString * p = LLRefInit(ptr, LJStringDealloc);
	if (p != NULL) {


	}
	return p;
}
static void LJStringDealloc(void * const p)
{
    //printf("%s called\n",__FUNCDNAME__);
}
