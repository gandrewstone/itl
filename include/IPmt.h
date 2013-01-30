/* Copyright (c) 2010 G. Andrew Stone, licensed under the  BSD 2 Clause license http://opensource.org/licenses/BSD-2-Clause
 ipmt.h: Intrusive Poor Man's Templating system
 */
#include "license.h"
#ifndef _IPMT_H_
#define _IPMT_H_

#ifdef __cplusplus
extern "C" {
#endif
    
    extern void* heapAllocate(unsigned long int amt);

    extern void heapFree(void* ptr);    
    
#define PtrT char*
#define PtrSzedInt unsigned long int    
#define WordT int

#define FieldOffset(typ, field) ((WordT) (PtrSzedInt) (&(((typ *) 0)-> field)))

typedef struct
{
  WordT objId;
  PtrT  first;

  /* This is a -1 terminated constant array of the offsets of pointers to parents in each node */
  WordT* parentOffsets;
  /* This is a -1 terminated constant array of the offsets of pointers to children in each node */
  WordT* childOffsets;
  /* This is the offset of a WordT 'mark' variable, used in some graph traversal algorithms. -1 if not supported  */
  WordT markOffset;
  
  WordT size;

  /** Internal flags relating to memory management, etc defined as enums below */
  WordT flags;
  /** A data item for your application to use to point to application data structures.  This is never touched by the container, except to initialize at construction time and clear when finalized. */
  PtrT cookie;
} ICnt;


enum
  {
    ICNT_ID = 0x48932838,
    INVALID_OFFSET = -1,    

    /* Flags */
    ALIVE   = 1,
    ALLOCED = 2,

    /* Commonly used indexes */
    Prev = 0,
    Next = 0,

    Parent = 0,
    Left   = 0,
    Right  = 1
  };


extern void ICntInit(ICnt* ths,WordT* parentOffsets, WordT* childOffsets,WordT markOffset);

extern void DilistInsert(ICnt* ths, PtrT elem, PtrT parent);
extern PtrT DilistRemove(ICnt* ths, PtrT elem);
extern void DilistPrepend(ICnt* ths, PtrT elem);
extern void DilistAppend(ICnt* ths, PtrT elem);
extern PtrT DilistPop(ICnt* ths);
extern void DilistPush(ICnt* ths, PtrT elem);


#ifdef __cplusplus
}
#endif


#endif 
