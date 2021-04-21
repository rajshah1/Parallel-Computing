CFLAGS=-O3 -std=c11 -g -fPIC -pthread -Xassembler -mrelax-relocations=no
CXXFLAGS=-O3 -std=c++17 -g -fPIC -pthread -Xassembler -mrelax-relocations=no
LDFLAGS=-pthread -fPIE
LDLIBS=libintegrate.a libfunctions.a
LD=g++

approx:
	$(LD) $(CXXFLAGS) $(LDFLAGS) approx.cpp $(LDLIBS) -o approx

libfunctions.a: functions.o
	ar rcs libfunctions.a functions.o

libintegrate.a: sequential_lib.o
	ar rcs libintegrate.a sequential_lib.o

%.pdf: %.tex
	pdflatex $<

ARXIVFILES=activity-parloop-static.pdf \
           approx.cpp libintegrate.a libfunctions.a Makefile .gitignore \
           params.sh test.sh clean.sh \
           sequential/bench_sequential.sh sequential/loopsample.cpp sequential/Makefile sequential/queue.sh sequential/seq_loop.hpp sequential/sequential.cpp \
           static/cases.txt static/Makefile static/plot.sh static/queue.sh static/run_static.sh static/static_sched.cpp \
           dynamic/cases.txt dynamic/dynamic_sched.cpp dynamic/Makefile dynamic/plot.sh dynamic/queue.sh dynamic/run_dynamic.sh




activity-parloop-static.tgz: $(ARXIVFILES)
	tar zcvf activity-parloop-static.tgz \
                         $(ARXIVFILES)
