/* Copyright (c) 2010 G. Andrew Stone, licensed under the  BSD 2 Clause license http://opensource.org/licenses/BSD-2-Clause */
#include "license.h"

/* Test/example of the non-intrusive singly linked list */

#include <malloc.h>
#include <stdio.h>

extern void ASSERT(int bool);

typedef struct MyData
{
  int i;
} MyData;



#include "Slist.h"

/* The non-intrusive version requires memory allocation for the list nodes */
void* SlistHeapAllocate(SlistHeadT* ths,unsigned long int amt)
{
  return malloc(amt);
}

void SlistHeapFree(SlistHeadT* ths,void* ptr)
{
  free(ptr);
}

void TestSlist(void)
{
  SlistHeadT* slist;
  MyData* mn = malloc(sizeof(MyData));
  MyData* mn2;

  slist = SlistCreate();
  SlistPrepend(slist, (void*) mn);

  mn2 = (MyData* ) SlistRemoveFirst(slist);
  ASSERT(mn == mn2);

  free(mn2);

  mn2 = (MyData* ) SlistRemoveFirst(slist);
  ASSERT(mn2 == 0);
  
  SlistFinalize(slist);
}
