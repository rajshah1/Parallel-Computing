#!/bin/sh

RESULTDIR=result/
PLOTDIR=plots/

# create result directory
if [ ! -d ${RESULTDIR} ];
then
    echo "ERROR: You must benchmark before making plots"
    exit 1
fi

# create plot directory
if [ ! -d ${PLOTDIR} ];
then
    mkdir ${PLOTDIR}
fi

THREADS="1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16"

# error checking
#   file existence
#   file populate
if [ ! -f ../sequential/result/sequential ] ;then
  echo ERROR: sequential benchmark not found
  echo go to the sequential directory and run \`make bench\' there
  exit 1
fi

for T in ${THREADS}; do
  if [ ! -s ${RESULTDIR}/fine_${T} ] ;then
    echo ERROR: ${RESULTDIR}/fine_${T} not found 
    echo run \'make bench\'  and WAIT for it to complete
    exit 1
  fi
done

if [ -f ./plots/plot.dat ]; then
  rm ./plots/plot.dat
fi

# plot data
for T in ${THREADS}; do
  echo "$T $(echo "scale=4; $(cat ../sequential/result/sequential)/$(cat ${RESULTDIR}fine_${T})" | bc)" >> ./plots/plot.dat
done


gnuplot << EOF
set terminal pdf;
set xlabel 'Processors';
set ylabel 'Speedup';
set key top left;

set output "./plots/Fine_Grain.pdf";
set title "Fine Grain";
plot './plots/plot.dat' t "point" lc 4 pt 1, './plots/plot.dat' t "line" lc 4 pt 1 with lines 

EOF




