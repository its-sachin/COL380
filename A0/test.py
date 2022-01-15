import subprocess
from matplotlib import pyplot as plt

T = 7
X = 10

def time():
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
    plt.savefig('time-analysis.png')
    plt.show()

def cachePerf():
    colour = ['c','g']
    for i in range(2):
        val = []
        for t in range(1,T):
            print(f'sudo perf stat -o outt -d -d -d make run x={X} t={t} type={i}')
            subprocess.run(f'sudo perf stat -o outt -d -d -d make run x={X} t={t} type={i}',shell=True)
            file = open('outt','r+')
            for l in file.readlines():
                line = []
                for j in l.split(' '):
                    if(j!=''):line.append(j)
                if(len(line) > 3 and line[1] == 'L1-dcache-load-misses'):val.append(float(line[3][:-1]))
        plt.xlabel('Number of Threads')
        plt.ylabel('L1-dcache-load-misses(%)')
        print(val)
        plt.plot([i for i in range(1,T)],val,colour[i], linewidth = 2, marker = 'o', label = f"Type = {i}")

    plt.legend(loc = 'upper left')
    plt.savefig('cache-analysis-perf.png')
    plt.show()

def cacheValgrind():
    colour = ['c','g']
    for i in range(2):
        val = []
        for t in range(1,T):
            print(f'valgrind --tool=cachegrind --log-file=outt make run x={X} t={t} type={i}')
            subprocess.run(f'valgrind --tool=cachegrind --log-file=outt make run x={X} t={t} type={i}',shell=True)
            file = open('outt','r+')
            for l in file.readlines():
                line = []
                for j in l.split(' '):
                    if(j!=''):line.append(j)
                if(len(line) > 3 and line[2]+line[3] == 'missrate:' and line[1] == 'D1'):val.append(float(line[4][:-1]))
        plt.xlabel('Number of Threads')
        plt.ylabel('D1 miss rate(%)')
        print(val)
        plt.plot([i for i in range(1,T)],val,colour[i], linewidth = 2, marker = 'o', label = f"Type = {i}")

    plt.legend(loc = 'upper left')
    plt.savefig('cache-analysis-valgrind.png')
    plt.show()

def check():
    f1 = open('out','r+').readlines()
    f2 = open('out2','r+').readlines()
    if(len(f1)!=len(f2)):print('LENGTH NOT SAME'); return 
    for i in range(1,len(f1)-2):
        if(f1[i]!=f2[i]):print('NOT SAME AT ',f1[i],f2[i])    

# cacheValgrind()
# cachePerf()
check()