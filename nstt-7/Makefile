EXECUTABLE=exec

CPP_SOURCES=src/test.cpp
CPP_HEADERS=src/emulator.hpp
OBJECTS=test.o

CXX=g++
CXXFLAGS=-Wall -Wextra -pedantic -std=c++17 -pthread
LIBS=-lgtest -lgtest_main

all: clean test

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)

test.o: $(CPP_SOURCES) $(CPP_HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@


clean:
	rm -f $(EXECUTABLE) $(OBJECTS)

test: $(EXECUTABLE)
	./$(EXECUTABLE)

.PHONY: clean test

