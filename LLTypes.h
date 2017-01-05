//
//  GlobalTypes.h
//  dataStruct
//
//  Created by li yajun on 16/3/31.
//  Copyright © 2016年 li yajun. All rights reserved.
//

#ifndef LLTypes_h
#define LLTypes_h

typedef void *              object_p;

typedef unsigned char       uint8;
typedef signed   char       int8;
typedef unsigned short      ushort;
typedef signed   short      sshort;
typedef unsigned int        uint;
typedef signed   int        sint;
typedef unsigned long       ulong;
typedef signed   long       slong;
typedef int                 ElementType;


typedef enum {
    NO  = 0,
    YES = 1,
}BOOL;

typedef enum {
    none =  0,
    same =  1,
    big  =  2,
    small = 3,
}obj_order;


static const  uint No_Find = (uint)-1;


#endif /*  LLTypes_h */
