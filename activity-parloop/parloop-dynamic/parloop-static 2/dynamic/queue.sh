#!/bin/sh


RESULTDIR=result/
h=`hostname`



if [ ! -e .passed_dynamic ];
then
    echo "You must pass all test before submitting"
    exit 1
fi

if [ ! -d ${RESULTDIR} ];
then
    mkdir ${RESULTDIR}
fi
    

# $THREADS
source ../params.sh

for thread in ${THREADS};
do
	qsub -q mamba -d "$(pwd)" -l nodes=1:ppn=16 -v THREAD=${thread} run_dynamic.sh -l walltime=03:00:00
done 
