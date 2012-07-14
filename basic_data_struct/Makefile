CROSS = 
CFLAGS = -g 
LDFLAGS = 
OBJ = $(patsubst %.c,%.o,$(wildcard *.c))
BINDIR = .
EXE = "${BINDIR}/exe"

$(EXE):$(OBJ)
	$(CROSS)gcc -o $@ $^ ${LDFLAGS}

.c.o:
	$(CROSS)gcc -c -o $@ $< $(CFLAGS)

clean:
	@rm -rf *.o ${EXE}

.PHONY: clean
