#------------------------------------------------------------------------------
SOURCE=./src/simulator.cpp
MYPROGRAM=simulator
LIBS= -std=c++11 -pthread
CC=g++

#------------------------------------------------------------------------------



all: $(MYPROGRAM)



$(MYPROGRAM): $(SOURCE)

	$(CC)  $(SOURCE) -o$(MYPROGRAM) $(LIBS) -static

clean:

	rm -f $(MYPROGRAM)
