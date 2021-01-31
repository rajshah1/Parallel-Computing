CFLAGS=-O3 -std=c11 -fPIC -Xassembler -mrelax-relocations=no
CXXFLAGS=-O3 -std=c++11 -fPIC -Xassembler -mrelax-relocations=no

LDFLAGS=-fPIE
LD=g++

hello: hello.o
	$(LD) $(LDFLAGS) hello.o -o hello

.PHONY: plot test bench clean

clean:
	-rm hello
	-rm hello.o

activity-hello.pdf: activity-hello.tex
	pdflatex $<

ARXIVFILES=activity-hello.pdf hello.cpp queue_hello.sh run_hello.sh Makefile .gitignore

activity-hello.tgz: $(ARXIVFILES)
	tar zcvf $@ $(ARXIVFILES)
