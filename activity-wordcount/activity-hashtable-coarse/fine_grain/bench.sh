#!/bin/sh


RESULTDIR=result/
h=`hostname`

echo running on ${h}

if [ "$h" = "mba-i1.uncc.edu"  ];
then
    echo Do not run this on the headnode of the cluster, use qsub!
    exit 1
fi
    
# debugging statments 
echo THREAD=${THREAD}: before starting time is $(date)
./main benchmark_sources.txt the 1000000 2>${RESULTDIR}/fine_${THREAD} >/dev/null
echo THREAD=${THREAD}: after ending time is $(date)
