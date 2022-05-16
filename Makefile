CFLAGS = -Wall -c
LDFLAGS = -lm # not really needed for this exercise
CC = gcc -std=c99
ECHO = echo "going to compile for target $@"
PROG = ex3_q1
all: $(PROG) test

ex3_q1: ex3_q1.o merger
	${CC} ${CCFLAGS} ex3_q1.o -o ex3_q1

ex3_q1.o: ex3_q1.c 
	$(CC) $(CFLAGS) ex3_q1.c -lm
	
merger: merger.o
	 ${CC} ${CCFLAGS} merger.o -o merger
	
merger.o: merger.c merger.h
	 $(CC) $(CFLAGS) merger.c -lm

clean:
	rm -vf *.o ${PROG} *.exe *.log *merged merger

test:
	@echo going to run test...
	./${PROG} x1 x2 x3 merged

	
	
	
