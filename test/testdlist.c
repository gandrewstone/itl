/* Copyright (c) 2010 G. Andrew Stone, licensed under the  BSD 2 Clause license http://opensource.org/licenses/BSD-2-Clause */
#include "license.h"

#include <malloc.h>
#include <stdio.h>

/* And the non-intrusive Dlist */
#include "Dlist.h"

typedef struct MyData
{
  int i;
} MyData;

/* The non-intrusive version requires memory allocation for the list nodes */
void* DlistHeapAllocate(DlistHeadT* ths,unsigned long int amt)
{
  return malloc(amt);
}

void DlistHeapFree(DlistHeadT* ths,void* ptr)
{
  free(ptr);
}


void TestDlist(void)
{
  DlistHeadT* list;
  MyData* mn = malloc(sizeof(MyData));
  MyData* mn2;

  list = DlistCreate();
  DlistPrepend(list, (void*) mn);

  mn2 = (MyData* ) DlistRemoveFirst(list);
  ASSERT(mn == mn2);

  free(mn2);

  mn2 = (MyData* ) DlistRemoveFirst(list);
  ASSERT(mn2 == 0);
  
  DlistFinalize(list);
}
