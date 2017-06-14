//
//  LJString.h
//  newDataStructPro
//
//  Created by li yajun on 17/1/9.
//  Copyright 2017 li yajun. All rights reserved.
//

#ifndef LJString_H
#define LJString_H
#include "LLRef.h"
#include "LLTypes.h"

typedef struct _LJNumber{
	LLRef   ref;
	sint    val;
}LJNumber;
extern LJNumber * LJNumberCreateByNum(sint m);

#endif /* LJString_h */
