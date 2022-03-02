import subprocess
import os

restart = 0.1
steps = 100
walks =30
rec = 20
seed = 369

# paths = [[8717,31525],[81867,545671],[82168,870161]]

# for i in paths:
#     for p1 in ([1,2,4,8,16]):
#         a1 = f'out_{p1}_{i[0]}_{i[1]}_{steps}_{walks}_{rec}_{seed}.dat'
#         for p2 in ([1,2,4,8,16]):
#             a2 = f'out_{p2}_{i[0]}_{i[1]}_{steps}_{walks}_{rec}_{seed}.dat'

#             subprocess.run(f'cmp {a1} {a2}', shell=True)

paths = []
for file in os.listdir():
    if file.startswith('run_') and file.__contains__('.sh.o'):
        paths.append(file)

paths.sort()

for i in paths:
    print(i,":")
    file = open(i, 'r')
    for line in file.readlines():
        print(line.strip('\n'))
    file.close()
    print()



        