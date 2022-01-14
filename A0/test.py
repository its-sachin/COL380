import subprocess
from matplotlib import pyplot as plt

T = 7
X = 10
colour = ['c','g']
for i in range(2):
    val = []
    for t in range(1,T):
        print(f'make run x={X} t={t} type={i} > outt')
        subprocess.run(f'make run x={X} t={t} type={i} > outt',shell=True)
        file = open('outt','r+')
        line = []
        for l in file.readlines():line=l.split(' ')
        val.append(float(line[-2]))
    plt.xlabel('Number of Threads')
    plt.ylabel('Time(ms)')
    print(val)
    plt.plot([i for i in range(1,T)],val,colour[i], linewidth = 2, marker = 'o', label = f"Type = {i}")

plt.legend(loc = 'upper left')
plt.savefig('type-analysis.png')
plt.show()