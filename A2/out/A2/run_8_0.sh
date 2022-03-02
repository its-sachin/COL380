cd $PBS_O_WORKDIR
module load compiler/gcc/9.1/openmpi/4.0.2
time mpirun -np 8 ./wtf data/8717_31525 8717 31525 0.1 100 30 20 369
