CXX=g++
STD=c++11
FLAGS=-Wall -Werror
RM=rm -f

SRCS=main.cpp
OBJS=main.o sorting_algorithms.o

all: main

main: $(OBJS)
	$(CXX) -std=$(STD) $(FLAGS) -o main $(OBJS) 

sorting_algorithms.o: sorting_algorithms.h sorting_algorithms.cpp

menu.o: menu.h menu.cpp

clean:
	$(RM) $(OBJS)
	rm main