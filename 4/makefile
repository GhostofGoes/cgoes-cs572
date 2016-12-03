BIN  = func
HW   = pas4
CC   = g++
SRCS = $(BIN).cpp $(BIN).h opList.cpp opList.h tree.cpp tree.h rand.h rand.cpp
LIBS = $(BIN).cpp opList.cpp tree.cpp rand.cpp
CCFLAGS = -Ofast -std=c++11

$(BIN): $(SRCS)
	$(CC) $(CCFLAGS) $(LIBS) -o $(BIN)

clean:
	# Rename files to .run if you want to save them
	rm -f $(BIN) *~ *.o *.output *.out $(HW).tar

tar:
	tar -cvf $(HW).tar $(SRCS) makefile # goes.pdf
	ls -l $(HW).tar

test: $(SRCS)
	make clean
	$(CC) $(CCFLAGS) -Wall -Wextra -g $(LIBS) -o $(BIN)

profile: $(SRCS)
	make clean
	$(CC) $(CCFLAGS) -p -g $(LIBS) -o $(BIN)

run:
	make
	time ./test.sh
