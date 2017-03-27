//  mem_allocator.h
//  dataStruct
//

#ifndef mem_allocator_h
#define mem_allocator_h


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define  Malloc(p)                  malloc((p))
#define  Free(p)                    free((p))
#define  Realloc(p, num)            realloc((p),(num))
#define  Calloc(count, size)        calloc((count), (size))
 
#define  StrnCpy(dest,src, count)   strncpy(dest, src, count)
#define  StrnCmp(dest,src, count)   strncmp(dest, src, count)
#define  StrnLen(src, count)		strnlen(src, count)
#define  StrLen(src)                strlen(src)
#define  MemCpy(dst, rsc, count)    memcpy(dst, rsc, count)
#define  MemSet(dst, val, size)     memset(dst, val, size)

#ifndef max
    #define max(a,b)   (a)>(b)? (a):(b)
#endif
#ifndef min
    #define min(a,b)   (a)<(b)? (a):(b)
#endif

#endif /* mem_allocator_h */
