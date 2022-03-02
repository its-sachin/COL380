from sys import argv
import time
import subprocess

restart = 0.1
steps = int(argv[2]) if len(argv) > 2 else 200
walks = int(argv[3]) if len(argv) > 3 else 50
rec = int(argv[4]) if len(argv) > 4 else 40
seed = 369

paths = [[8717,31525],[81867,545671],[82168,870161]]

for proc in ([1,2,4,8,16]):
    j = 0
    for i in paths:
        file = open(f'run_{proc}_{j}.sh', 'w')
        path = 'data/' +f'{i[0]}_{i[1]}'
        a = "time " + f'mpirun -np {proc} ./wtf {path} {i[0]} {i[1]} {restart} {steps} {walks} {rec} {seed}'
        print(a)
        file.write('cd $PBS_O_WORKDIR\nmodule load compiler/gcc/9.1/openmpi/4.0.2\n')
        file.write(a + '\n')
        j+=1
        file.close()




