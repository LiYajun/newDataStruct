
#include <stdio.h>
#include "LLArray.h"
#include "LLTArray.h"

#define Printf(value)  \
printf( #value "\n"   )

#define Str(A) #A
#define Con(A,B)   A##B
#define Str2(A,B)  Str(Con(A,B))

#define PRINT(FORMAT,VALUE)   printf("The value "#VALUE" is "#FORMAT" \n",  VALUE)
int main(int argc, char * argv[])
{
    
    LLTArray * ary  = LLTArrayCreate();
    LLRef * obj = LLRefCreate();
    LLArrayAddObject((LLArray*)ary, obj);
    
    LLRefRelease(ary);
    printf("ary release");
    LLRefRelease(obj);
	printf("hello world!\n");
}
