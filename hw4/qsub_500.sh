#!/bin/bash
#PBS -N MatMul_MUid
#PBS -l walltime=1:00:00
#PBS -l mem=4GB
#PBS -l nodes=1:ppn=1
cd $PBS_O_WORKDIR
MAT_SIZE=500
BLOCK_SIZE=50
for rep in `seq 1 5`
do
 /usr/bin/time -v ./MatMul $MAT_SIZE 0
 /usr/bin/time -v ./MatMul $MAT_SIZE $BLOCK_SIZE
done
# end of script