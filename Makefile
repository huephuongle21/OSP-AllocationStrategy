.default: all

all: main

clean:
	rm -f main *.o

main: main.o Utility.o AllocationStrategy.o BestFit.o FirstFit.o LinkedList.o MemoryBlock.o WorstFit.o
	g++ -Wall -Werror --std=c++11 -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror --std=c++11 -O -g -c $^
