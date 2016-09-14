BIN  = decipher
HW   = pas2
CC   = g++
SRCS = $(BIN).cpp rand.h rand.cpp 
LIBS = -lm $(BIN).cpp rand.cpp
CCFLAGS = -O3 # -O4 # -Ofast # -g # -std=gnu++11

$(BIN): $(SRCS)
	$(CC) $(CCFLAGS) $(OBJS) $(LIBS) -o $(BIN)

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
	$(CC) $(CCFLAGS) -Wall -g $(OBJS) $(LIBS) -o $(BIN)
	
full-test:
	touch $(SRCS)
	make test
