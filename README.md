itl
===

Intrusive poor man's template library for C.  This library provides basic intrusive list data structures that are written using poor man's templates (PMT).  PMTs are a means of using #define macros and include files to essentially implement templates in C.  "Intrusive" data structures put their pointers within the structure itself, rather then in a separately allocated structure.  There is a bit of ugliness using PMTs but the end result are reusable thread-safe, type-safe, optimal-memory-use data structures.