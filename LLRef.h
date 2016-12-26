#ifndef _LLREF_H_
#define _LLREF_H_

typedef struct
{
	int retainCount;
	//void * me;
}LLRef;

extern LLRef * LLRefCreate(void);
extern void LLRefInit(void * ptr);
extern int LLRefRelease(void * ptr);
extern int LLRefRetain(void * ptr);

#endif // !_LLREF_H_


