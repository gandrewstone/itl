/* Copyright (c) 2010 G. Andrew Stone, licensed under the  BSD 2 Clause license http://opensource.org/licenses/BSD-2-Clause */
#include "license.h"
#include "Slist.h"

#define PmtPrefix   sl
#define PmtNodeType SlistT
#define PmtField    next
#define Scope       static
#undef  PmtNoFuncDecl
#define PmtNoStructDecl
#include "IslistImpl.h"
#undef PmtPrefix   
#undef PmtNodeType 
#undef PmtField    
#undef Scope

extern SlistHeadT extra;

static SlistT* MakeWrapper(SlistHeadT* ths, PtrT elem)
{
  SlistT* w = (SlistT*) SlistHeapAllocate(ths,sizeof(SlistT));
  w->next = 0;
  w->data = elem;
  return w;
}

static void ReleaseWrapper(SlistHeadT* ths, SlistT* w)
{
  w->next = 0;
  w->data = 0;  
  SlistHeapFree(ths,w);
}

SlistHeadT* SlistCreate (void)
{
  SlistHeadT* ths = (SlistHeadT*) SlistHeapAllocate(NULL,sizeof(SlistHeadT));
  slInit(ths);
  ths->cnt.flags |= ALLOCED;
}

void SlistFinalize(SlistHeadT* ths)
{
  ASSERT(ths && (ths->cnt.objId == ICNT_ID) && (ths->cnt.flags & ALIVE));

  WordT flags = ths->cnt.flags;
  ths->cnt.flags = 0; /* ear the alive flag (and all other flags as a side effect) */

  if (flags&ALLOCED) SlistHeapFree(NULL,ths);
}

void SlistInit (SlistHeadT* ths)
{
  slInit(ths);
}

void SlistPrepend (SlistHeadT* ths, PtrT data)
{
  SlistT* elem = MakeWrapper(ths,data);
  slPrepend(ths,elem);
}

void SlistAppend (SlistHeadT* ths, PtrT data)
{
  SlistT* elem = MakeWrapper(ths,data);
  slAppend(ths,elem);
}

void SlistPush (SlistHeadT* ths, PtrT data)
{
  SlistT* elem = MakeWrapper(ths,data);
  slPush(ths,elem);
}

PtrT SlistRemoveFirst (SlistHeadT* ths)
{
  PtrT ret;
  SlistT* elem = slRemoveFirst(ths);

  if (!elem) return 0;
  ret = elem->data;
  ReleaseWrapper(ths,elem);
  return ret;
}

PtrT SlistPop (SlistHeadT* ths)
{
  return SlistRemoveFirst(ths);
}
