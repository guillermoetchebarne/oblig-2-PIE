all : libHamming.a codificarHamming decodificarHamming
COPT=-Wall -ansi -ggdb
LDFLAGS=-L./
LDLIBS=-lHamming -lbits -lm

codificarHamming: codificarHamming.o codificarHamming.h
			cc $(COPT) -o $@ codificarHamming.o $(LDFLAGS) $(LDLIBS)  

decodificarHamming: decodificarHamming.o decodificarHamming.h
			cc $(COPT) -o $@ decodificarHamming.o $(LDFLAGS) $(LDLIBS)
.c.o:
			cc $(COPT) -c $<

libHamming.a: libHamming.o
			ar rcs $@ $<