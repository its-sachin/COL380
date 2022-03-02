cd $PBS_O_WORKDIR
module load compiler/gcc/9.1/openmpi/4.0.2
time mpirun -np 16 ./wtf data/81867_545671 81867 545671 0.1 100 30 20 369