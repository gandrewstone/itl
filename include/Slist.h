/* Copyright (c) 2010 G. Andrew Stone, licensed under the  BSD 2 Clause license http://opensource.org/licenses/BSD-2-Clause */
#include "license.h"
#include "IPmt.h"
#include <stddef.h>

typedef struct SlistT
{
  struct SlistT*  next;
  PtrT            data;
} SlistT;

#define PmtPrefix   sl
#define PmtNodeType SlistT
#define PmtField    next
#define Scope       static
#define PmtNoFuncDecl
#undef  PmtNoStructDecl
#include "Islist.h"
#undef PmtPrefix   
#undef PmtNodeType 
#undef PmtField    
#undef Scope      
#undef PmtNoFuncDecl


/* Predeclare the structures */
typedef struct slHeadT SlistHeadT;



SlistHeadT* SlistCreate ();

void SlistFinalize(SlistHeadT* ths);

void SlistPrepend (SlistHeadT* ths, PtrT elem);

void SlistAppend (SlistHeadT* ths, PtrT elem);

void SlistPush (SlistHeadT* ths, PtrT elem);

PtrT SlistRemoveFirst (SlistHeadT* ths);

PtrT SlistPop (SlistHeadT* ths);

/* You must supply implementations for these functions.
NULL will be passed as the ths pointer if there is no associated Slist
(for example if it is the allocation/free of the SlistHeadT itself).

This allows you to have different allocators for different lists
 */
extern     void* SlistHeapAllocate(SlistHeadT* ths,size_t length);
extern     void SlistHeapFree(SlistHeadT* ths,void* object);



