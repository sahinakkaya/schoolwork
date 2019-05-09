CXX=g++
STD=c++11
FLAGS=-Wall -Werror
RM=rm -f

SRCS=main.cpp
OBJS=main.o ingredient.o stock.o helper_functions.o menu.o order.o

all: main

main: $(OBJS)
	$(CXX) -std=$(STD) $(FLAGS) -o main $(OBJS) 

ingredient.o: ingredient.h ingredient.cpp
stock.o: stock.h stock.cpp
order.o: order.h order.cpp
helper_functions.o: helper_functions.h helper_functions.cpp

menu.o: menu.h menu.cpp

clean:
	$(RM) $(OBJS)
	rm main
