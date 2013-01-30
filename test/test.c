/* Copyright (c) 2010 G. Andrew Stone, licensed under the  BSD 2 Clause license http://opensource.org/licenses/BSD-2-Clause */
#include "license.h"

#include <malloc.h>
#include <stdio.h>

extern void TestDlist(void);
extern void TestSlist(void);


typedef struct MyNodeT
{
  int i;
  struct MyNodeT* next;
} MyNodeT;



/* Create an intrusive singly linked list with the MyNodeT structure */
#define PmtPrefix   TestList
#define PmtNodeType MyNodeT
#define PmtField    next
#include "IslistImpl.h"
#undef Scope
#undef PmtPrefix   
#undef PmtNodeType 
#undef PmtField


void ASSERT(int bool)
{
  if (!bool)
  {
    printf("ASSERTION FAILED");
  }
}


/* This example uses the doubly linked list directly rather then wrapping a poor
   man's template around it.  This style is not recommended but is possible. */

typedef struct MyDNodeT
{
  struct MyNodeT* prev;
  int i;
  struct MyNodeT* next;

} MyDNodeT;


void TestDilist(void)
{
  int i;
  WordT parentOffsets[] = { FieldOffset(MyDNodeT, prev), INVALID_OFFSET };
  WordT childOffsets[] = { FieldOffset(MyDNodeT, next), INVALID_OFFSET };
  ICnt  dlist;
  
  MyDNodeT n[5];
  for (i=0;i<5;i++) n[i].i = i;

  ICntInit(&dlist, parentOffsets,childOffsets, INVALID_OFFSET); 

  DilistAppend(&dlist, (PtrT) &n[1]);
  DilistAppend(&dlist, (PtrT)&n[2]);
  DilistAppend(&dlist, (PtrT)&n[3]);
  DilistPrepend(&dlist, (PtrT)&n[0]);
  printf("\ndlist: ");
  for (i=0;i<4;i++)
    {
      MyDNodeT* tmp = (MyDNodeT*) DilistPop(&dlist);
      if (tmp) printf (" %d ", tmp->i);
    }
}






int main(void)
{
  TestListHeadT tlh;

  TestListInit(&tlh);

  MyNodeT a={},b={},c={},d={};

  a.i = 1;
  b.i = 2;
  c.i = 3;
  d.i = 4;

  TestListPush(&tlh,&b);
  TestListPrepend(&tlh,&a);
  TestListAppend(&tlh,&c);
  TestListAppend(&tlh,&d);

  MyNodeT *tmp;

  do
    {
    tmp = TestListPop(&tlh);
    if (tmp) printf("tmp = %d ", tmp->i);
    } while(tmp);
  

  TestSlist();
  TestDlist();
  TestDilist();
  return 0;
}
