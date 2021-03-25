#!/bin/sh

if [ -f "./main" ]; then
  qsub -d `pwd` -l nodes=1:ppn=1 -q mamba -l walltime=00:10:00 -l mem=100gb bench.sh
else
  echo -e "\nERROR!\nUnable to benchmark!\nYou must compile first with \"make\""
fi
