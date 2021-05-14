CFLAGS=-O3 -std=c11 -g -fPIC -pthread
CXXFLAGS=-O3 -std=c++17 -g -fPIC -pthread
LDFLAGS=-pthread
LDLIBS=../libfunctions.a
LD=g++

.PHONY: plot dynamic_sched

all: dynamic_sched

approx:
	$(LD) $(CXXFLAGS) $(LDFLAGS) ../approx.cpp $(LDLIBS) -o ../approx

dynamic_sched: dynamic_sched.o
	$(LD) $(LDFLAGS) dynamic_sched.o $(LDLIBS) -o dynamic_sched

bench: dynamic_sched
	./queue.sh 

test: dynamic_sched approx
	./../test.sh dynamic cases.txt

plot: 
	./plot.sh

clean:
	./../clean.sh
