#!/bin/sh

PLOTDIR=plot/
RESULTDIR=result/

if [ ! -d ${PLOTDIR} ];
then
    mkdir ${PLOTDIR}
fi

gnuplot <<EOF
set terminal pdf
set output '${PLOTDIR}/time_plots.pdf'

set xlabel 'n'
set ylabel 'time (in seconds)'

set style data linespoints

set key top left
plot '${RESULTDIR}/time_inten_1' t "intensity=1" lc 1, \
     '${RESULTDIR}/time_inten_10' t "intensity=10" lc 6, \
     '${RESULTDIR}/time_inten_100' t "intensity=100" lc 3, \
     '${RESULTDIR}/time_inten_1000' t "intensity=1000" lc 4

plot 'result/time_inten_1' t "intensity=1" lc 1

plot 'result/time_inten_10' t "intensity=10" lc 6

plot 'result/time_inten_100' t "intensity=100" lc 3

plot 'result/time_inten_1000' t "intensity=1000" lc 4

EOF
