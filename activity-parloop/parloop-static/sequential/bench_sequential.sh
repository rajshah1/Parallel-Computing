#!/bin/sh

RESULTDIR=result/
h=`hostname`

if [ "$h" = "mba-i1.uncc.edu"  ];
then
    echo Do not run this on the headnode of the cluster, use qsub!
    exit 1
fi

if [ ! -d ${RESULTDIR} ];
then
    mkdir ${RESULTDIR}
fi
    


source ../params.sh

echo running on ${h}
echo seq: starting bench at $(date)

for intensity in $INTENSITIES;
do
    for n in $NSPLOT;
    do
	./sequential 1 0 10 ${n} ${intensity} 2>${RESULTDIR}/sequential_${n}_${intensity}  >/dev/null
    done
done

echo seq: ending bench at $(date)
