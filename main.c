
#include <stdio.h>
#include "LLArray.h"

#define Printf(value)  \
printf( #value "\n"   )

#define Str(A) #A
#define Con(A,B)   A##B
#define Str2(A,B)  Str(Con(A,B))

#define PRINT(FORMAT,VALUE)   printf("The value "#VALUE" is "#FORMAT" \n",  VALUE)
int main(int argc, char * argv[])
{
    LLArray * ptr = LLArrayCreate();
    
 
    for(int i=0; i<5; i++){
        LLRef * obj   = LLRefCreate();
        LLArrayAddObject(ptr, obj);
    }
    LLRef * obj   = LLRefCreate();

    LLArrayInsertAt(ptr, obj, 3);
   // for(int i=99; i>=0; i--)
   //     LLArrayRemoveAt(ptr, i);
   
	printf("hello world!\n");
}
