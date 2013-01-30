/* Copyright (c) 2010 G. Andrew Stone, licensed under the  BSD 2 Clause license http://opensource.org/licenses/BSD-2-Clause */
#include "license.h"
#include "Dlist.h"

static int parentOffsets[] = { 0 /*FieldOffset(DlistT, prev) */, INVALID_OFFSET };
static int childOffsets[] = { sizeof(PtrT) /* FieldOffset(DlistT, next)*/, INVALID_OFFSET };


static DlistT* MakeWrapper(DlistHeadT* ths,PtrT elem)
{
    DlistT* w = (DlistT*) DlistHeapAllocate(ths,sizeof(DlistT));
  w->prev = 0;
  w->next = 0;
  w->data = elem;
  return w;
}

static void ReleaseWrapper(DlistHeadT* ths,DlistT* w)
{
  w->prev = 0;
  w->next = 0;
  w->data = 0;  
  DlistHeapFree(ths,w);
}

DlistHeadT* DlistCreate()
{
    DlistHeadT* ths = (DlistHeadT*) DlistHeapAllocate(NULL,sizeof(DlistHeadT));  
  DlistInit(ths);
  ths->flags |= ALLOCED;
  return ths;
}

void          DlistInit(DlistHeadT* ths)
{
  ICntInit(ths,parentOffsets,childOffsets,INVALID_OFFSET);
  ths->flags |= ALIVE;
}

void          DlistFinalize(DlistHeadT* ths)
{
  ASSERT(ths && (ths->objId == ICNT_ID) && (ths->flags & ALIVE));

  WordT flags = ths->flags;
  ths->flags = 0; /* clear the alive flag (and all other flags as a side effect) */

  if (flags&ALLOCED) DlistHeapFree(NULL,ths);
}


void          DlistPrepend (DlistHeadT* ths, PtrT data)
{
  DlistT* elem = MakeWrapper(ths,data);  
  DilistPrepend(ths, (PtrT) elem);
}

void          DlistAppend (DlistHeadT* ths, PtrT data)
{
  DlistT* elem = MakeWrapper(ths,data);  
  DilistAppend(ths, (PtrT) elem);
}


void          DlistPush (DlistHeadT* ths, PtrT data)
{
  DlistT* elem = MakeWrapper(ths,data);  
  DilistPush(ths, (PtrT) elem);  
}

PtrT       DlistRemoveFirst (DlistHeadT* ths)
{
   return DlistPop(ths);
}

PtrT       DlistPop (DlistHeadT* ths)
{
  PtrT ret;
  DlistT* elem = (DlistT*) DilistPop(ths);
  if (!elem) return 0;
  ret = elem->data;
  ReleaseWrapper(ths, elem);
  return ret;
}
