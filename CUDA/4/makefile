BIN  = func
CC   = g++
SRCS = $(BIN).cpp $(BIN).h opList.cpp opList.h tree.cpp tree.h rand.h rand.cpp population.cpp population.h chromosome.cpp chromosome.h
LIBS = $(BIN).cpp opList.cpp tree.cpp rand.cpp population.cpp chromosome.cpp
CCFLAGS = -std=c++11 # -Ofast

$(BIN): $(SRCS)
	$(CC) $(CCFLAGS) $(LIBS) -o $(BIN)

clean:
	# Rename files to .run if you want to save them
	rm -f $(BIN) *~ *.o *.output *.out $(HW).tar *.s

tar:
	tar -cvf $(BIN).tar $(SRCS) makefile
	ls -l $(BIN).tar

test: $(SRCS)
	make clean
	$(CC) $(CCFLAGS) -Wall -Wextra -g $(LIBS) -o $(BIN)

profile: $(SRCS)
	make clean
	$(CC) $(CCFLAGS) -p -g $(LIBS) -o $(BIN)

assembly: $(SRCS)
	$(CC) $(CCFLAGS) -S $(LIBS)
