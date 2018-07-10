CXX=g++
CXXFLAGS=-Wall -pedantic -std=c++11

DEPS=timer.h

%.o: %.c $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

pomot: timer.o pomot.cpp
	$(CXX) -o pomot timer.o pomot.cpp
