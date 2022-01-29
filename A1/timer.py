import sys
import subprocess
from matplotlib import pyplot as plt

data = sys.argv[1]
thread = int(sys.argv[2])

subprocess.run('make', shell=True)

times = []
for t in range(1,thread+1):
    subprocess.run(f'make run data={data} thread={t} > out.txt',shell=True)
    f = open('out.txt','r+')
    for l in f.readlines():
        print(l.strip('\n'))
        line = l.split(' ')
        if(line[0] == 'Time'):times.append(float(line[-1][:-3]))
print(times)

plt.xlabel('Thread #')
plt.ylabel('Time(ms)')
plt.plot([i for i in range(1,thread+1)],times,'c', linewidth = 2, marker = 'o')
plt.show()