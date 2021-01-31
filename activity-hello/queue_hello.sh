qsub -q mamba -d "$(pwd)" -l walltime=00:10:00 -l nodes=1:ppn=1 run_hello.sh
