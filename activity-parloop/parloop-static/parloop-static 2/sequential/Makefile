CFLAGS=-O3 -std=c11 -g -fPIC -pthread
CXXFLAGS=-O3 -std=c++17 -g -fPIC -pthread
LDFLAGS=-pthread
LDLIBS=../libintegrate.a ../libfunctions.a
LD=g++

all: sequential 

sequential: sequential.o 
	$(LD) $(LDFLAGS) sequential.o $(LDLIBS) -o sequential

bench: sequential
	./queue.sh 

clean:
	./../clean.sh

