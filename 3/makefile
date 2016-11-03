BIN  = points
HW   = pas3
CC   = g++
SRCS = $(BIN).cpp $(BIN).h population.cpp population.h chromosome.cpp chromosome.h rand.h rand.cpp
LIBS = -lm $(BIN).cpp population.cpp chromosome.cpp rand.cpp
CCFLAGS = -O3 -std=c++11

$(BIN): $(SRCS)
	$(CC) $(CCFLAGS) $(LIBS) -o $(BIN)

all:    
	touch $(SRCS)
	make

clean:
	# Rename files to .run if you want to save them
	rm -f $(BIN) *~ *.o *.output $(HW).tar

tar:
	tar -cvf $(HW).tar $(SRCS) makefile goes.pdf
	ls -l $(HW).tar
	
test: $(SRCS)
	make clean
	$(CC) $(CCFLAGS) -Wall -Wextra -g $(LIBS) -o $(BIN)

debug: $(SRCS)
	make clean
	$(CC) -std=c++11 -Wall -Wextra -g $(LIBS) -o $(BIN)

profile: $(SRCS)
	make clean
	$(CC) -p -g $(LIBS) -o $(BIN)

full-test:
	touch $(SRCS)
	make test
