CROSS = 
CFLAGS = -g  -I../inc/
LDFLAGS = 
OBJ = $(patsubst %.c,%.o,$(wildcard *.c))
BINDIR = ../bin/
EXE = "${BINDIR}alg"

$(EXE):$(OBJ)
	$(CROSS)gcc -o $@ $^ ${LDFLAGS}

.c.o:
	$(CROSS)gcc -c -o $@ $< $(CFLAGS)

clean:
	@rm -rf *.o ${EXE}

.PHONY: clean
