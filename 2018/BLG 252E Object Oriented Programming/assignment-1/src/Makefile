CXX=g++
STD=c++11
FLAGS=-Wall -Werror
RM=rm -f

SRCS=main.cpp
OBJS=main.o vector.o polynomial.o

all: main

main: $(OBJS)
	$(CXX) -std=$(STD) $(FLAGS) -o main $(OBJS) 

vector.o: vector.h vector.cpp
polynomial.o: polynomial.h polynomial.cpp

clean:
