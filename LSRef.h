#ifndef __LSREF_H__
#define __LSREF_H__


#include "LLTypes.h"
#include "mem_allocator.h"
#include <stdio.h>


typedef void *LSRefPtr;


// �����޸����ü���֮����������   
typedef void(*RetainFunc)(LSRefPtr pRef);
typedef void(*ReleaseFunc)(LSRefPtr pRef);

// ��������ͷ�Ref��Դ����������
typedef void(*DeallocFunc)(LSRefPtr pRef);

// ��ӡ����                                                                
typedef void(*DisplayFunc)(LSRefPtr pRef, uint offset);


/************************************************************************\
 ����                                                                  
\************************************************************************/
typedef struct
{
    sint            retainCount;
    RetainFunc      retain;
    ReleaseFunc     release;
    DeallocFunc     dealloc;
    DisplayFunc     display;
} LSRef;

LSRef *LSRefCreate(void);


/************************************************************************\
 ͨ�÷���                                                                    
\************************************************************************/
LSRef *LSInit(LSRefPtr ptr,
              RetainFunc retainF,
              ReleaseFunc releaseF,
              DeallocFunc deallocF,
              DisplayFunc displayF);

sint LSRetain(LSRefPtr ptr);

sint LSRelease(LSRefPtr ptr);

void LSDisplay(LSRefPtr ptr);


#endif // !__LSREF_H__
