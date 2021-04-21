#!/bin/sh

RESULTDIR=result/
SEQ_RESULTDIR=../sequential/result/
PLOTDIR=plot/
h=`hostname`


if [ ! -d ${PLOTDIR} ];
then
    mkdir ${PLOTDIR}
fi


. ../params.sh


# ensure sequential was run

for intensity in $INTENSITIES;
do
    for n in $NSPLOT;
    do
        if [ ! -s "${SEQ_RESULTDIR}sequential_${n}_${intensity}" ]];
        then
            echo Go to the \'sequential\' directory and run \'make bench\' before plotting
            exit 1
        fi
        if [ ! -s "${RESULTDIR}static_${n}_${intensity}_1" ]];
        then
            echo Run \'make bench\' and let all jobs finish before plotting
            exit 1
        fi
    done
done


#preparing files for plotting

for intensity in $INTENSITIES;
do
    for n in $NSPLOT;
    do
	    for thread in ${THREADS};
	    do
		#output in format "thread seqtime partime"
		echo ${thread} \
		     $(cat ${SEQ_RESULTDIR}/sequential_${n}_${intensity}) \
		     $(cat ${RESULTDIR}/static_${n}_${intensity}_${thread})
	    done > ${RESULTDIR}/speedup_static_${n}_${intensity}
    done
done

for thread in ${THREADS};
do
    for n in $NSPLOT;
    do
	    for intensity in ${INTENSITIES};
	    do
		#output in format "intensity seqtime partime"
		echo ${intensity} \
		     $(cat ${SEQ_RESULTDIR}/sequential_${n}_${intensity}) \
		     $(cat ${RESULTDIR}/static_${n}_${intensity}_${thread})
	    done > ${RESULTDIR}/speedupi_static_${n}_${thread}
    done
done


for intensity in $INTENSITIES;
do
    for thread in ${THREADS};
    do
	    for n in $NSPLOT;
	    do
		#output in format "n seqtime partime"
		echo ${n} \
		     $(cat ${SEQ_RESULTDIR}/sequential_${n}_${intensity}) \
		     $(cat ${RESULTDIR}/static_${n}_${intensity}_${thread})
	    done > ${RESULTDIR}/speedupn_static_${thread}_${intensity}
    done
done


#Speedup plots

for intensity in $INTENSITIES;
do
	GCMDSP="${GCMDSP} ; set key top left; \
			    set key title 'N'; \
                            set xlabel 'threads'; \
                            set ylabel 'speedup'; \
                            set xrange [1:20]; \
                            set yrange [0:20]; \
                            set ytics 2; \
                            set title 'intensity=$intensity'; "
	GCMDSP="${GCMDSP} ; plot "
	c=1
    for n in $NSPLOT;
    do
        GCMDSP="${GCMDSP}   '${RESULTDIR}/speedup_static_${n}_${intensity}' u 1:(\$2/\$3) t '$n' lc ${c} lw 3, " 
	c=`expr $c + 1`
    done
done

#for intensity in $INTENSITIES;
#do
#	GCMDSP="${GCMDSP} ; set key top left; \
#                            set xlabel 'threads'; \
#                            set ylabel 'speedup'; \
#                            set xrange [1:20]; \
#                            set yrange [1:20]; \
#                            set title 'thread intensity=$intensity'; "
#	GCMDSP="${GCMDSP} ; plot "
#	c = 1
#    for n in $NSPLOT;
#    do
#        GCMDSP="${GCMDSP}   ''${RESULTDIR}/speedup_static_${n}_${intensity}_thread' u 1:(\$2/\$3) lc ${c} t '$n', "
#	c='expr $c + 1'
#    done
#done





for intensity in $INTENSITIES;
do
    for thread in ${THREADS};
    do
	GCMDSPN="${GCMDSPN} ; set key top left; \
                            set xlabel 'n'; \
                            set ylabel 'speedup'; \
                            set logscale x 10; \
                            set xrange [*:*]; \
                            set yrange [0:20]; \
                            set ytics 2; \
                            set title'thread=${thread} intensity=${intensity}'; \
                plot '${RESULTDIR}/speedupn_static_${thread}_${intensity}' u 1:(\$2/\$3) lc 3 lw 3 t 'parloop'; "
    done
done

for n in $NSPLOT;
do
    for thread in ${THREADS};
    do
	GCMDSPI="${GCMDSPI} ; set key top left; \
                            set xlabel 'intensity'; \
                            set ylabel 'speedup'; \
                            set xrange [*:*]; \
                            set yrange [0:20]; \
                            set ytics 2; \
                            set title'thread=${thread} n=${n}'; \
                plot '${RESULTDIR}/speedupi_static_${n}_${thread}' u 1:(\$2/\$3) lc 3 lw 3 t 'parloop'; "
    done
done



#speedup as a function of n



gnuplot <<EOF
set terminal pdf
set output '${PLOTDIR}/static.pdf'
set style data linespoints
${GCMDSP}
EOF


gnuplot <<EOF
set terminal pdf
set output '${PLOTDIR}/static_compare.pdf'
set style data linespoints
${GCMDSPN}
${GCMDSPI}
EOF
