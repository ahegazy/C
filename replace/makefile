IDIR =includes
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj

LIBS=-lm

_DEPS = replace.h textman.h 
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o replace.o textman.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bin/replace: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean #keeps make from missing with anyfile named clean.

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 