#!/bin/sh

if [ ! -e .passed ];
then
    echo "You must pass all test before submitting"
    exit 1
fi

qsub -d  "$(pwd)" queue_job.pbs
