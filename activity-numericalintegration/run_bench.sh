#!/bin/sh

RESULTDIR=result/
h=`hostname`

if [ "$h" = "mba-i1.uncc.edu"  ];
then
    echo Do not run this on the headnode of the cluster, use bench.sh to submit the job!
    exit 1
fi

if [ ! -d ${RESULTDIR} ];
then 
    mkdir ${RESULTDIR}
fi

INTENSITIES="1 10 100 1000"
NS="`seq 1 10` `seq 20 10 100` `seq 200 100 1000` `seq 2000 1000 10000` `seq 20000 10000 100000` `seq 200000 100000 1000000` `seq 2000000 1000000 10000000` `seq 20000000 10000000 100000000`"
#NS="`seq 1 10`"


for intensity in $INTENSITIES;
do
    for n in $NS;
    do
	echo $n\ $(./main 1 0 10 ${n} ${intensity} 2>&1 >/dev/null)
    done > ${RESULTDIR}time_inten_${intensity}
done 
