#
VERSION      := 0.1
DEBUG        := 1
# PROFILE      := 1

# Discover all the files
Hfiles  := $(wildcard *.h)
Cfiles  := $(wildcard *.cpp) $(wildcard *.c) $(wildcard *.pde)
Ofiles  := $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(Cfiles)))

CF      := -I. -I../include

CC      := gcc

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

all: test 

../libitl.a:
	(cd ../src; $(MAKE))

test: test.o testslist.o testdlist.o ../libitl.a
	$(CC) $(LF) -o $@ test.o testslist.o testdlist.o ../libitl.a

clean:
	-rm -f *.o test

cleanall:
	-rm -f *.o test ../src/*.o ../*.so ../*.a

%.o: %.cpp $(Hfiles)
	$(CC) $(CF) -o $@ $<

%.o: %.c $(Hfiles)
	$(CC) $(CF) -o $@ $<
