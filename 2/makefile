BIN  = decipher
HW   = pas2
CC   = g++
SRCS = $(BIN).cpp rand.h rand.cpp evolve.cpp evolve.h
LIBS = -lm $(BIN).cpp rand.cpp evolve.cpp
CCFLAGS = -O3

$(BIN): $(SRCS)
	$(CC) $(CCFLAGS) $(LIBS) -o $(BIN)

all:    
	touch $(SRCS)
	make

clean:
	# Rename files to .run if you want to save them
	rm -f $(BIN) *~ *.o *.output $(HW).tar

tar:
	tar -cvf $(HW).tar $(SRCS) makefile freq.txt goes.pdf
	ls -l $(HW).tar
	
test: $(SRCS)
	make clean
	$(CC) $(CCFLAGS) -Wall -g $(LIBS) -o $(BIN)

debug: $(SRCS)
	make clean
	$(CC) -Wall -g $(LIBS) -o $(BIN)

full-test:
	touch $(SRCS)
	make test
