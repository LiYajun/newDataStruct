
#include <stdio.h>
#include "LLArray.h"
#include "LLTArray.h"
#include <string.h>
#include "mem_allocator.h"
#include "LJNumber.h"
#include <signal.h>
#include "LJHashTable.h"

#define Printf(value)  \
printf( #value "\n"   )

#define Str(A) #A
#define Con(A,B)   A##B
#define Str2(A,B)  Str(Con(A,B))

#define PRINT(FORMAT,VALUE)   printf("The value " #VALUE " is " #FORMAT " \n",  VALUE)
#define LLPrintf(a,...)  printf(a"\n",##__VA_ARGS__)
#define PP(a, ...)  printf(a,  __VA_ARGS__)
#define ppt(a,b)    printf(a, ##b)

void testString()
{
	char * key = "abcdefg";
	uint   len = strnlen(key, 0xFF);
	char * key2 = Malloc(sizeof(char)*(len + 1));
	key2 = strncpy(key2, key, len + 1);
	char s[] = "hello world";
	strncpy(s, "shit!", 5);
	puts(s);
	printf("%s", key2);
}
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

#if defined(__LSREF_H__)
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
#endif
void sigHandler(int sig)
{
	printf("test signal!");
}
int main(int argc, char * argv[])
{
    //signal(SIGABRT, &sigHandler);
    //raise(SIGFPE);
	LJHashTable * table = LJHashTableCreate( );
	LJNumber * number = LJNumberCreateByNum(2);
	uint retain = number->ref.retainCount;
	LJHashTableInsert(table, number, "key");
	retain = number->ref.retainCount;
	LJNumber * number1 = LJHashTableObjectForKey(table, "key");
	LJHashTableInsert(table, number, "key");
	retain = number->ref.retainCount;
	LLRefRelease(number);

	LLRefRelease(number);

 
	printf("retain count = %d", number1->val);
    getchar();

    return 0;
}
