CPP = g++
CPPFLAGS = -Wall -Werror -std=c++11
SOURCES=$(wildcard ./*.cpp)
OBJECTS = $(patsubst %.cpp, %.o, $(SOURCES))

main: $(OBJECTS)
	$(CPP) $(CPPFLAGS) -o $@ $^
	rm -rf *.o

$(OBJECTS): $(SOURCES)
	$(CPP) $(CPPFLAGS) -c $(SOURCES)

clean:
	rm -rf *.o
	rm main

