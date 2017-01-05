
#include <stdio.h>
#include "LLArray.h"
int main(int argc, char * argv[])
{
    LLArray * ptr = LLArrayCreate();
    LLRef * obj   = LLRefCreate();
    
    LLArrayInsertAt(ptr, obj, 0);
    LLArrayRemoveAt(ptr, 0);
    LLRefRelease(obj);
	printf("hello world!");
}
