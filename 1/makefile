BIN  = localsearch
CC   = g++
SRCS = $(BIN).cpp $(BIN).h rand.h rand.cpp bitHelpers.h bitHelpers.cpp
LIBS = -lm $(BIN).cpp rand.cpp bitHelpers.cpp mapFunctions.cpp
CCFLAGS = -g -O3 # -std=gnu++11

$(BIN): $(SRCS)
	$(CC) $(CCFLAGS) $(OBJS) $(LIBS) -o $(BIN)

all:    
	touch $(SRCS)
	make

clean:
	rm -f $(BIN) $(BIN).tar *~ $(BIN).output *.o

tar:
	tar -cvf pas1.tar $(SRCS) makefile
	ls -l pas1.tar
	
test: $(SRCS)
	$(CC) $(CCFLAGS) -Wall $(OBJS) $(LIBS) -o $(BIN)
	
full-test:
	touch $(SRCS)
	make test
