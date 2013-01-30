
all:
	cd src; $(MAKE)
	cd test; $(MAKE)

clean:
	-rm -f src/*.o test/*.o test/test *.a *.so
