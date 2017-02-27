//
//  LJString.h
//  newDataStructPro
//
//  Created by li yajun on 17/1/9.
//  Copyright © 2017年 li yajun. All rights reserved.
//

#ifndef LJString_H
#define LJString_H
#include "LLRef.h"
#include "LLTypes.h"

typedef struct _LJString{
	LLRef   ref;
	uint    length;
	char *  value;
}LJString;

extern LLRefPtr LJStringInit(LLRefPtr const p, const char * str);
#endif /* LJString_h */
