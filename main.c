
#include <stdio.h>
#include "LLArray.h"

#define Printf(value)  \
printf( #value "\n"   )

#define Str(A) #A
#define PRINT(FORMAT,VALUE)   printf("The value "#VALUE" is "#FORMAT" \n",  VALUE)
int main(int argc, char * argv[])
{
    LLArray * ptr = LLArrayCreate();
    LLRef * obj   = LLRefCreate();
    
    LLArray * ptr2 = ptr;
    LLRefRetain(ptr2);
    
    LLArrayInsertAt(ptr, obj, 0);
    LLArrayRemoveAt(ptr, 0);
    LLRefRelease(obj);
    int a = 10;
   
	printf("hello world!\n");
}
