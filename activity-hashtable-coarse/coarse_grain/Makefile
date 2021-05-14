SRCS = main.cpp
EXE = main

# Everything below that should not have to change ever.

CXX=g++
LD=g++
CC=g++

TARGET =  all

OBJS = $(SRCS:.cpp=.o)

CXXFLAGS = -g  -std=c++17 -O3

LDFLAGS = -g -lstdc++fs  -pthread

$(EXE): $(OBJS)
	$(CXX) -o $(EXE) $(OBJS) $(LDFLAGS) $(LIBS)

.SUFFIXES: .cpp

.cpp.o:  
	$(CXX) $(CXXFLAGS) -c $< -o $@

all : $(EXE)

run:
	./main test_sources.txt the 1000000

test:
	./test.sh

bench:
	./queue.sh

plot:
	./plot.sh

clean:
	-rm $(OBJS)
	-rm $(EXE)
	-rm .passed
	-rm bench.sh.*
	-rm ./result/ -r
	-rm ./plots/ -r
