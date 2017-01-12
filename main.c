
#include <stdio.h>
#include "LLArray.h"
#include "LLTArray.h"

#include "LSRef.h"
#include "LSArray.h"


#define Printf(value)  \
printf( #value "\n"   )

#define Str(A) #A
#define Con(A,B)   A##B
#define Str2(A,B)  Str(Con(A,B))

#define PRINT(FORMAT,VALUE)   printf("The value " #VALUE " is " #FORMAT " \n",  VALUE)
#define LLPrintf(a,...)  printf(a"\n",##__VA_ARGS__)
#define PP(a, ...)  printf(a,  __VA_ARGS__)
#define ppt(a,b)    printf(a, ##b)


void testLYJ()
{
    LLPrintf("//////////////////////--LYJ--///////////////////");

    LLTArray * ary  = LLTArrayCreate();
    LLArray  * array = LLArrayCreate();

    LLArrayAddObject(array, ary);

    LLPrintf("array release%d", 1);
    LLRefRelease(array);
    LLPrintf("ary release %d", 2);
    LLRefRelease(ary);


    // LLRefRelease(obj);
    PP("%d %d\n", 100034, 34345);

    LLPrintf("////////////////////////////////////////////////");
}


void testLS()
{
    LLPrintf("//////////////////////--LS--////////////////////");

    LSRef *ref1 = LSRefCreate();
    LSDisplay(ref1);

    LSRef *ref2 = LS_RETAIN(ref1);
    LSDisplay(ref1);
    LS_RELEASE(ref2);
    LSDisplay(ref1);

    LLPrintf("-------------------------");
    LSRef *ref3 = LSRefCreate();
    LSRef *ref4 = LSRefCreate();
    LSArray *array1 = LSArrayCreate();
    LSArray *array2 = LSArrayCreate();

    LSArrayAdd(array1, ref1);
    LSArrayAdd(array1, ref4);
    LSArrayAdd(array1, array2);
    LSArrayAdd(array2, ref3);

    LS_RELEASE(ref1);

    LSDisplay(array1);
    LSDisplay(array2);

    LS_RELEASE(array1);
    LSDisplay(array2);

    LLPrintf("////////////////////////////////////////////////");
}


int main(int argc, char * argv[])
{
    testLYJ();
    LLPrintf("\n\n");
    testLS();

    getchar();

    return 0;
}
