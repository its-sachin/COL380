import subprocess
# from matplotlib import pyplot as plt

T = 7
X = 10

def time():
    colour = ['c','g']
    for i in range(2):
        val = []
        for t in range(1,T):
            print('make run x='+str(X) + ' t='+str(t) + ' type='+str(i) + ' > outt')
            subprocess.run('make run x='+str(X)+' t='+str(t)+' type='+str(i)+' > outt',shell=True)
            file = open('outt','r+')
            line = []
            for l in file.readlines():line=l.split(' ')
            val.append(float(line[-2]))
        # plt.xlabel('Number of Threads')
        # plt.ylabel('Time(ms)')
        print(val)
    #     plt.plot([i for i in range(1,T)],val,colour[i], linewidth = 2, marker = 'o', label = "Type = " + str(i))

    # plt.legend(loc = 'upper left')
    # plt.savefig('time-analysis.png')
    # plt.show()

def cache():
    colour = ['c','g']
    for i in range(2):
        val = []
        for t in range(1,T):
            print('sudo perf stat -o outt -d -d -d make run x='+str(X)+' t='+str(t)+' type='+str(i))
            subprocess.run('sudo perf stat -o outt -d -d -d make run x='+str(X)+' t='+str(t)+' type='+str(i),shell=True)
            file = open('outt','r+')
            for l in file.readlines():
                line = []
                for j in l.split(' '):
                    if(j!=''):line.append(j)
                if(len(line) > 3 and line[1] == 'L1-dcache-load-misses'):val.append(float(line[3][:-2]))
        # plt.xlabel('Number of Threads')
        # plt.ylabel('L1-dcache-load-misses(%)')
        print(val)
    #     plt.plot([i for i in range(1,T)],val,colour[i], linewidth = 2, marker = 'o', label = "Type = " + str(i))

    # plt.legend(loc = 'upper left')
    # plt.savefig('cache-analysis.png')
    # plt.show()

time()