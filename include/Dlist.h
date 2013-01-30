/* Copyright (c) 2010 G. Andrew Stone, licensed under the  BSD 2 Clause license http://opensource.org/licenses/BSD-2-Clause */
#include "license.h"
#include "IPmt.h"

#include <stddef.h>

typedef struct DlistT
{
  struct DlistT* next;
  struct DlistT* prev;
  PtrT           data;
} DlistT;

/* Predeclare the structures */
typedef ICnt DlistHeadT;

DlistHeadT* DlistCreate();

void          DlistInit(DlistHeadT* ths);

void          DlistFinalize(DlistHeadT* ths);


void          DlistPrepend (DlistHeadT* ths, PtrT data);

void          DlistAppend (DlistHeadT* ths, PtrT data);

void          DlistPush (DlistHeadT* ths, PtrT data);

PtrT          DlistRemoveFirst (DlistHeadT* ths);

PtrT          DlistPop (DlistHeadT* ths);

/* You must supply implementations for these functions.
NULL will be passed as the ths pointer if there is no associated Dlist
(for example if it is the allocation/free of the DlistHeadT itself).

This allows you to have different allocators for different lists
 */
extern     void* DlistHeapAllocate(DlistHeadT* ths,size_t length);
extern     void DlistHeapFree(DlistHeadT* ths,void* object);

