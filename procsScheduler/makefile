IDIR =includes
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj

_DEPS = general.h  RR.h FCFS.h statistics.h 
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o general.o FCFS.o RR.o statistics.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bin/scheduler: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) 

.PHONY: clean #keeps make from missing with anyfile named clean.

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
