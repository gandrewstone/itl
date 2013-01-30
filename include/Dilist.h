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
/* The thread synchronization objects also need to be defined */
/*
#define PmtMutexT
#define PmtCondT  
*/

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
#define PmtAssert(x)
#endif

/* ---- */

#include "IPmt.h"  /* Generic container implementation */


#define Eval(x) x

#define N2(x,y) x ## y
#define N(x,y) N2(x,y)

#ifndef PmtNoStructDecl
typedef struct N(PmtPrefix, HeadT)
{
  ICnt cnt;
  PmtNodeType* end;
  WordT parent;
  WordT child[2];
  WordT flags;

  PmtThreadSafe(PmtMutexT exclusion);
  PmtThreadWake(PmtCondT  alert);
} N(PmtPrefix, HeadT);
#endif

#ifndef PmtNoFuncDecl
Scope void N(PmtPrefix, Init) (N(PmtPrefix, HeadT)* ths);

Scope void N(PmtPrefix, Prepend) (N(PmtPrefix, HeadT)* ths, PmtNodeType* elem);

Scope void N(PmtPrefix, Append) (N(PmtPrefix, HeadT)* ths, PmtNodeType* elem);

Scope void N(PmtPrefix, Push) (N(PmtPrefix, HeadT)* ths, PmtNodeType* elem);

Scope PmtNodeType* N(PmtPrefix, RemoveFirst) (N(PmtPrefix, HeadT)* ths);

#if 0
Scope PmtNodeType* N(PmtPrefix, RemoveLast) (N(PmtPrefix, HeadT)* ths);

#endif


Scope PmtNodeType* N(PmtPrefix, Pop) (N(PmtPrefix, HeadT)* ths);

#if 0 /* use an iterator */
Scope PmtNodeType* N(PmtPrefix, First) (N(PmtPrefix, HeadT)* ths);

Scope PmtNodeType* N(PmtPrefix, Next) (N(PmtPrefix, HeadT)* ths, PmtNodeType* elem);

Scope PmtNodeType* N(PmtPrefix, Last) (N(PmtPrefix, HeadT)* ths);

#endif

#endif

#if 0
#undef PmtPrefix
#undef PmtNodeType
#undef PmtField
#undef Scope
#endif
