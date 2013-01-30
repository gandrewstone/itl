#
VERSION      := 0.1
DEBUG        := 1
# PROFILE      := 1

# Discover all the files
Hfiles  := $(wildcard *.h)
Cfiles  := $(wildcard *.cpp) $(wildcard *.c) $(wildcard *.pde)
Ofiles  := $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(Cfiles)))

CCC     := g++
CC      := gcc
LIB     := ar -cvq
SOLIB   := gcc -shared -o
# -Wl-soname,<name>

CF      := -fPIC -I. -I../include

ifdef DEBUG
CF      += -c -g -O0
LF      := 
else
ifdef PROFILE
CF      += -c -g -O2 -pg
LF      := -pg
else
CF      += -c -O2
endif
endif

all: ../libitl.a ../libitl.so

../libitl.a: $(Ofiles)
	$(LIB) $@ $^

../libitl.so: $(Ofiles)
	$(SOLIB) $@ $^


clean:
	-rm -f *.o test

%.o: %.cpp $(Hfiles)
	$(CC) $(CF) -o $@ $<

%.o: %.c $(Hfiles)
	$(CC) $(CF) -o $@ $<
