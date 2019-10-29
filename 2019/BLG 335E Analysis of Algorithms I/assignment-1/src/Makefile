CXX=g++
STD=c++11
FLAGS=-Wall -Werror
RM=rm -f

OBJS=main.o sorting_algorithms.o

all: main

main: $(OBJS)
	$(CXX) -std=$(STD) $(FLAGS) -o main $(OBJS) 

sorting_algorithms.o: sorting_algorithms.h sorting_algorithms.cpp

clean:
	$(RM) $(OBJS)
	rm main
