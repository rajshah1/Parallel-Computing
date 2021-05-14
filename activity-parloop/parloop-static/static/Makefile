CFLAGS=-O3 -std=c11 -g -fPIC -pthread
CXXFLAGS=-O3 -std=c++17 -g -fPIC -pthread
LDFLAGS=-pthread
LDLIBS=../libfunctions.a
LD=g++

.PHONY: plot static_sched

all: static_sched

approx:
	$(LD) $(CXXFLAGS) $(LDFLAGS) ../approx.cpp $(LDLIBS) -o ../approx

static_sched: static_sched.o
	$(LD) $(LDFLAGS) static_sched.o $(LDLIBS) -o static_sched

bench: static_sched
	./queue.sh 

test: static_sched approx
	./../test.sh static cases.txt 

plot: 
	./plot.sh  

clean:
	./../clean.sh
