

#include <stdio.h>
#include "LJLinkList.h"

#include "LLArray.h"
#include "LLTArray.h"
#include <string.h>
#include "mem_allocator.h"
#include "LJNumber.h"
#include <signal.h>
#include "LJHashTable.h"
#include "NumStack.h"
#include "StackQueue.h"
#include "LJBigNum.h"

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

void testHashTable()
{
	LJHashTable * table = LJHashTableCreate();
	LJNumber * number = LJNumberCreateByNum(2);
	uint retain = number->ref.retainCount;
	LJHashTableInsert(table, number, "key");
	retain = number->ref.retainCount;
	LJNumber * number1 = LJHashTableObjectForKey(table, "key");
	LJHashTableInsert(table, number, "key");
	retain = number->ref.retainCount;
	LLRefRelease(number);

	LLRefRelease(number);

    LLRefRelease(table);
	printf("retain count = %d", number1->val);
}

BOOL testPalindrome(const char * str)
{
	uint i;
	BOOL flag = YES;
	ulong len = StrLen(str);

	NumStack * stack = createStack(100);
	for (i = 0; i<len; i++)
		stackPush(stack, str[i]);

	for (i = 0; i < len; i++)
	{
		char val1 = str[i];
		char val2 = stackPop(stack);
		if (val1 != val2) {
			flag = NO;
			break;
		}
	}
	stackClear(stack);
	return  flag;
}
void testStackQueue()
{
	NumQueue * que = createQueue(100);
	sint val[10] = { 0,1,2,3,4,5,6,7,8,9 };
	for (uint i = 0; i < 10; i++)
		appendTail(que, val[i]);
	for (uint i = 0; i < 10; i++)
	{
		sint val = deleteHead(que);
		printf("val:%d\n", val);
	}
	QueueClear(que);
}
void testBigNum()
{
	LJBigNum * bigNum1 = LJBigNumCreteByStr(    "9876543210");
	bigNum1->sign = Sign_negative;
	LJBigNum * bigNum2 = LJBigNumCreteByStr("98459876543210");
	bigNum2->sign = Sign_Positive;
	LJBigNumAddOther(bigNum1, bigNum2);
	char * newStr = "12343456789";
	uint  len = StrLen(newStr);
	LJBigNumSetNum(bigNum1, newStr, len);
	LJBigNumPrintValues(bigNum1);
    LLRefRelease(bigNum1);
    LLRefRelease(bigNum2);
}
void testLJLinkList()
{
    LJLinkList * linkList = LJLinkListCreate();
    
    LJNumber * num1 = LJNumberCreateByNum(1234);
    LJNumber * num2 = LJNumberCreateByNum(2234);
    LJLinkListAddObj(linkList, num1);
    LJLinkListAddObj(linkList, num2);
    LJNumber * temp = LJLinkListGetHeadObj(linkList);
    printf("head node num value:%d\n", temp->val);
    LLRefRelease(num1);
    LLRefRelease(num2);
    printf("num1 count:%d\n", num1->ref.retainCount);
    printf("num2 count:%d\n", num2->ref.retainCount);
    LLRefRelease(linkList);
    printf("num1 count:%d\n", num1->ref.retainCount);
    printf("num2 count:%d\n", num2->ref.retainCount);
}
void sigHandler(int sig)
{
	printf("test signal!");
}
int main(int argc, char * argv[])
{
    //signal(SIGABRT, &sigHandler);
    //raise(SIGFPE);
	//testPalindrome("bacdf");
	//testStackQueue();
	//testBigNum();
    testLJLinkList();
    getchar();

    return 0;
}

