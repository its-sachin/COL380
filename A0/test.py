import subprocess
import sys
from matplotlib import pyplot as plt

T = 7
X = 10
colour = ['c','g']
Type = ['Original Code', 'Modified Code']
def time():
    for i in range(2):
        val = []
        for t in range(1,T):
            print(f'make test x={X} t={t} type={i} > outt')
            subprocess.run(f'make test x={X} t={t} type={i} > outt',shell=True)
            file = open('outt','r+')
            line = []
            for l in file.readlines():line=l.split(' ')
            val.append(float(line[-2]))
        plt.xlabel('Number of Threads')
        plt.ylabel('Time(ms)')
        print(val)
        plt.plot([i for i in range(1,T)],val,colour[i], linewidth = 2, marker = 'o', label = Type[i])

    plt.legend(loc = 'upper left')
    plt.savefig('time-analysis.png')
    plt.show()

def cachePerf():
    colour = ['c','g']
    for i in range(2):
        val = []
        allData = []
        for t in range(1,T):
            print(f'sudo perf stat -o outt -d -d -d make test x={X} t={t} type={i}')
            subprocess.run(f'sudo perf stat -o outt -d -d -d make test x={X} t={t} type={i}',shell=True)
            file = open('outt','r+')
            for l in file.readlines():
                line = []
                allData.append(l)
                for j in l.split(' '):
                    if(j!=''):line.append(j)
                if(len(line) > 3 and line[1] == 'L1-dcache-load-misses'):val.append(float(line[3][:-1]))
            allData.append('\n')
        plt.xlabel('Number of Threads')
        plt.ylabel('L1-dcache-load-misses(%)')
        print(val)
        plt.plot([i for i in range(1,T)],val,colour[i], linewidth = 2, marker = 'o', label = Type[i])

        wr = open(f'perf-{Type[i][0]}.txt','w+')
        for line in allData:wr.write(line)

    plt.legend(loc = 'upper left')
    plt.savefig('cache-analysis-perf.png')
    plt.show()

def cacheValgrind():
    X=3
    colour = ['c','g']
    for i in range(2):
        val = []
        allData = []
        for t in range(1,T):
            print(f'valgrind --tool=cachegrind --log-file=outt ./classify rfile dfile 1009072 {t} {X} {i}')
            subprocess.run(f'valgrind --tool=cachegrind --log-file=outt ./classify rfile dfile 1009072 {t} {X} {i}',shell=True)
            file = open('outt','r+')
            for l in file.readlines():
                line = []
                allData.append(l)
                for j in l.split(' '):
                    if(j!=''):line.append(j)
                if(len(line) > 3 and line[2]+line[3] == 'missrate:' and line[1] == 'D1'):val.append(float(line[4][:-1]))
            allData.append('\n')
        plt.xlabel('Number of Threads')
        plt.ylabel('D1 miss rate(%)')
        print(val)
        plt.plot([i for i in range(1,T)],val,colour[i], linewidth = 2, marker = 'o', label = Type[i])

        wr = open(f'valgrind-{Type[i][0]}.txt','w+')
        for line in allData:wr.write(line)

    plt.legend(loc = 'upper left')
    plt.savefig('cache-analysis-valgrind.png')
    plt.show()
    X=10

def check():
    f1 = open('out','r+').readlines()
    f2 = open('out2','r+').readlines()
    if(len(f1)!=len(f2)):print('LENGTH NOT SAME'); return 
    for i in range(1,len(f1)-2):
        if(f1[i]!=f2[i]):print('NOT SAME AT ',f1[i],f2[i])    

def gprof():
    for i in range(2):
        allData = []
        for t in range(1,T):
            commands = [f'make test t={t} x={X} type={i}', 'gprof --flat-profile classify >outt'] 
            for com in commands:
                print(com)
                subprocess.run(com,shell=True)
                allData.append(com + '\n')

            file = open('outt','r+')
            for l in file.readlines():
                allData.append(l)
            allData.append('-----------------------------------------------------------------------\n')

        wr = open(f'gprof-{Type[i][0]}.txt','w+')
        for line in allData:wr.write(line)

mode = sys.argv[1]
if(mode == 't'):time()
elif(mode == 'cp'):cachePerf()
elif(mode == 'cv'):cacheValgrind()
elif(mode=='c'):check()
elif(mode=='g'):gprof()
else:
    print('Chceking time')
    time()

    print('Chceking cache perf')
    cachePerf()

    print('Chceking cache valgrind')
    cacheValgrind()

    print('Chceking gprof')
    gprof()