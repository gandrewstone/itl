/* Copyright (c) 2010 G. Andrew Stone, licensed under the  BSD 2 Clause license http://opensource.org/licenses/BSD-2-Clause */
#include "license.h"
/* Poor man's template to generate a bunch of container data structures */

/* Parameters to the template */

#ifndef PmtPrefix 
#error "You must define PmtPrefix to specialize the name of your list"
#endif

#ifndef PmtNodeType
#error "You must define PmtNodeType to identify what data structure will be used"
#endif

#ifndef PmtField
#error "You must define PmtField to identify the 'next' pointer field name"
#endif


/* By default, a metric is just an integer */
#ifndef PmtMetricInt
#define PmtMetricInt WordT
#define PmtMetricIntSet(x,val) x = val 
#endif

/* By default, thread safety is Off */
#ifndef PmtThreadSafe
#define PmtThreadSafe(x)
#endif


/* By default, thread waking is Off */
#ifndef PmtThreadWake
#define PmtThreadWake(x)
#endif

/* By default the scope is global, not static */
#ifndef Scope  
#define Scope
#endif

/* By default thread mutex is off */
#ifndef PmtLock
#define PmtLock(head)
#endif
#ifndef PmtUnlock
#define PmtUnlock(head)
#endif

#ifndef PmtAssert
/* By default no assert is used */
#define PmtAssert(x)
#endif

/* ---- */

#include "IPmt.h"  /* Generic container implementation */


#define Eval(x) x

#define N2(x,y) x ## y
#define N(x,y) N2(x,y)

#include "Islist.h"

Scope void N(PmtPrefix, Init) (N(PmtPrefix, HeadT)* ths)
{
  ths->cnt.parentOffsets = &ths->parent;
  ths->parent = -1; /* No parent pointer */

  ths->cnt.childOffsets  = ths->child; 
  ths->child[0] = FieldOffset(PmtNodeType, PmtField);
  ths->child[1] = -1;
  
  ths->cnt.markOffset = -1; /* No mark */

  /* ear the first and last pointers */
  ths->cnt.first = 0;
  ths->end = 0;

  ths->cnt.objId = ICNT_ID;
  ths->cnt.flags = ALIVE;
  ths->cnt.cookie = 0;
}

Scope void N(PmtPrefix, Prepend) (N(PmtPrefix, HeadT)* ths, PmtNodeType* elem)
{
  PmtAssert(ths);
  PmtLock(ths);

  PmtAssert(elem);
  PmtAssert(elem->PmtField == 0);  /* its not on another list */
  

  elem->PmtField = (PmtNodeType*) ths->cnt.first;
  
  if (ths->cnt.first == 0) ths->end = elem;  /* If the first node NULL, this is both the first and last node on the list */
  ths->cnt.first = (PtrT) elem;
  
  PmtUnlock(ths);
}

Scope void N(PmtPrefix, Append) (N(PmtPrefix, HeadT)* ths, PmtNodeType* elem)
{
  PmtAssert(ths);
  PmtLock(ths);
  PmtAssert(elem);
  PmtAssert(elem->PmtField == 0);  /* its not on another list */

  /* if the list is empty, prepending is the same as appending */
  if (!ths->end) N(PmtPrefix, Prepend) (ths, elem);
  else
    {
      PmtAssert(ths->end->PmtField == 0);  /* Last node should have no child */
      ths->end->PmtField = elem;
      ths->end = elem;
    }

  PmtUnlock(ths);
}

Scope void N(PmtPrefix, Push) (N(PmtPrefix, HeadT)* ths, PmtNodeType* elem)
  {
    N(PmtPrefix, Prepend) (ths, elem);
  }


Scope PmtNodeType* N(PmtPrefix, RemoveFirst) (N(PmtPrefix, HeadT)* ths)
{
  PmtNodeType* elem;
  PmtAssert(ths);
  PmtLock(ths);

  elem = (PmtNodeType*) ths->cnt.first;
  if (elem)
    {
      ths->cnt.first = (PtrT) elem->PmtField;
      
      /* If we dequeue the last element, then set end to NULL */
      if (ths->end == elem) ths->end = 0;

      elem->PmtField = 0;
    }
 
  PmtUnlock(ths);
  return elem;
}

#if 0
Scope PmtNodeType* N(PmtPrefix, RemoveLast) (N(PmtPrefix, HeadT)* ths)
{
  PmtNodeType* elem;
  PmtAssert(ths);
  PmtLock(ths);
 
  


  PmtUnlock(ths);
  return elem;
}
#endif


Scope PmtNodeType* N(PmtPrefix, Pop) (N(PmtPrefix, HeadT)* ths)
{
  return N(PmtPrefix, RemoveFirst) (ths);
}


#if 0 /* use an iterator */
Scope PmtNodeType* N(PmtPrefix, First) (N(PmtPrefix, HeadT)* ths)
{
  PmtAssert(ths);
  return (PmtNodeType*) ths->cnt.first;
}

Scope PmtNodeType* N(PmtPrefix, Next) (N(PmtPrefix, HeadT)* ths, PmtNodeType* elem)
{
  PmtAssert(ths);

}

Scope PmtNodeType* N(PmtPrefix, Last) (N(PmtPrefix, HeadT)* ths)
{
  PmtAssert(ths);

}
#endif


#if 0
#undef PmtPrefix
#undef PmtNodeType
#undef PmtField
#undef Scope
#endif
