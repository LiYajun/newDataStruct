
#include <stdio.h>
#include "LLArray.h"
#include "LLTArray.h"

#define Printf(value)  \
printf( #value "\n"   )

#define Str(A) #A
#define Con(A,B)   A##B
#define Str2(A,B)  Str(Con(A,B))

#define PRINT(FORMAT,VALUE)   printf("The value " #VALUE " is " #FORMAT " \n",  VALUE)
#define LLPrintf(a,...)  printf(a"\n",##__VA_ARGS__)
#define PP(a, ...)  printf(a,  __VA_ARGS__)
#define ppt(a,b)    printf(a, ##b)
int main(int argc, char * argv[])
{
    
    LLTArray * ary  = LLTArrayCreate();
    LLArray  * array = LLArrayCreate();
   
    LLArrayAddObject(array, ary);
    
    LLPrintf("array release%d",1);
    LLRefRelease(array);
    LLPrintf("ary release %d",2);
    LLRefRelease(ary);
    
    
  //  LLRefRelease(obj);
    PP("%d %d\n", 100034,34345);
	printf("hello world!\n");
}
