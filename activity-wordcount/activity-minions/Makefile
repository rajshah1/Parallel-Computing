CXXFLAGS=-std=c++17
LDLIBS=-lpthread

run: minions
	./minions 40

minions:

activity-minions.pdf: activity-minions.tex
	pdflatex $<

FILESTOINCLUDE=Makefile activity-minions.pdf minions.cpp

activity-minions.tgz: $(FILESTOINCLUDE)
	tar zcvf $@ $(FILESTOINCLUDE)
