CXX=g++
CXXFLAGS=-Wall -pedantic -std=c++11
BINARIES=pomot

DEPS=timer.h worklog.h

%.o: %.c $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

pomot: timer.o worklog.o pomot.cpp
	$(CXX) -o pomot timer.o worklog.o pomot.cpp -lmpg123 -lao
.PHONY: clean

clean:
	rm -f $(BINARIES) *.o
