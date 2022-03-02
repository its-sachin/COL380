cd $PBS_O_WORKDIR
module load compiler/gcc/9.1/openmpi/4.0.2
time mpirun -np 1 ./wtf data/82168_870161 82168 870161 0.1 100 30 20 369
