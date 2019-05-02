CXX=g++
STD=c++11
FLAGS=-Wall -Werror
RM=rm -f

SRCS=main.cpp
OBJS=main.o ingredient.o

all: main

main: $(OBJS)
	$(CXX) -std=$(STD) $(FLAGS) -o main $(OBJS) 

ingredient.o: ingredient.h ingredient.cpp

clean:
	$(RM) $(OBJS)
	rm main
