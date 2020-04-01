#------------------------------------------------------------------------------
SOURCE=./src/simulator.cpp
MYPROGRAM=simulator
LIBS= -lncurses -std=c++11 -pthread -fopenmp
CC=g++

#------------------------------------------------------------------------------



all: $(MYPROGRAM)



$(MYPROGRAM): $(SOURCE)

	$(CC) $(SOURCE) -o$(MYPROGRAM) $(LIBS)

clean:

	rm -f $(MYPROGRAM)
