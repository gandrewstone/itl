/* Copyright (c) 2010 G. Andrew Stone, licensed under the  BSD 2 Clause license http://opensource.org/licenses/BSD-2-Clause */
#include "license.h"
#include "IPmt.h"

#include <assert.h>

#define Prev(elem,ths) ((PtrT*) (elem + (ths->parentOffsets[Prev])))
#define Next(elem,ths) ((PtrT*) (elem + (ths->childOffsets[Next])))


void ICntInit(ICnt* ths,WordT* parentOffsets, WordT* childOffsets,WordT markOffset)
{
  ths->objId  = ICNT_ID;
  ths->first  = 0;
  ths->size   = 0;
  ths->flags  = 0;
  ths->cookie = 0;

  ths->parentOffsets = parentOffsets;
  ths->childOffsets  = childOffsets;
  ths->markOffset    = markOffset;
}



#if 0
void DilistSelectedMerge(ICnt* ths, ICnt* that,WordT (*cmp)(PtrT a, PtrT b))
{
  PtrT* a = ths->first;
  PtrT* astart = a;
  PtrT* b = that->first;
  PtrT* bstart = b;

  if (b == 0) return;

  do
    {
      if (!b) return;
            

    } while (astart != Next(ths,a));  
}
#endif


void DilistInsert(ICnt* ths, PtrT elem, PtrT parent)
{
  if (parent == 0) /* Empty list case */
    {
      assert(ths->first == 0);
      ths->first = elem;
      *Next(elem,ths)   = elem;
      *Prev(elem,ths)   = elem;
    }
  else /* Normal case */
    {
      PtrT child    = *Next(parent,ths);
  
      *Next(parent,ths) = elem;
      *Prev(elem,ths)   = parent;

      *Prev(child,ths)  = elem;
      *Next(elem,ths)   = child;
    }
}

PtrT DilistRemove(ICnt* ths, PtrT elem)
{
  if (elem == 0) return elem;

  PtrT p =   *Prev(elem, ths);
  PtrT n =   *Next(elem, ths);
  
  *Next(p,ths) = n;
  *Prev(n,ths) = p;

  *Next(elem,ths) = 0;
  *Prev(elem,ths) = 0;

  if (ths->first == elem) 
    {
      if (n==elem) ths->first = 0;
      else ths->first = n;
    }

  return elem;
}

PtrT DilistPop(ICnt* ths)
{
  return DilistRemove(ths,ths->first);
}

void DilistPush(ICnt* ths, PtrT elem)
{
  return DilistPrepend(ths,elem);
}


void DilistPrepend(ICnt* ths, PtrT elem)
{
  DilistAppend(ths, elem);  /* its a circular linked list, so if I append and then move the first pointer, I've prepended! */
  ths->first = elem;
}

void DilistAppend(ICnt* ths, PtrT elem)
{
  if (ths->first == 0) DilistInsert(ths, elem, 0);
  else DilistInsert(ths, elem, *Prev(ths->first,ths)); /* Its a circular linked list, so this is getting me the last element */
}
