BIN  = localsearch
CC   = g++
SRCS = $(BIN).cpp rand.h rand.cpp bitHelpers.h bitHelpers.cpp
LIBS = -lm $(BIN).cpp rand.cpp bitHelpers.cpp
CCFLAGS = -O3 # -O4 # -Ofast # -g # -std=gnu++11

$(BIN): $(SRCS)
	$(CC) $(CCFLAGS) $(OBJS) $(LIBS) -o $(BIN)

all:    
	touch $(SRCS)
	make

clean:
	# Rename files to .run if you want to save them
	rm -f $(BIN) *~ *.o *.output pas1.tar

tar:
	tar -cvf pas1.tar $(SRCS) makefile
	ls -l pas1.tar
	
test: $(SRCS)
	$(CC) $(CCFLAGS) -Wall $(OBJS) $(LIBS) -o $(BIN)
	
full-test:
	touch $(SRCS)
	make test
