file = open('outt','r+')
got=False; tid=0; values=[]
for line in file.readlines():
    l = line.split(' ')
    if(l[0] == 'thread'):
        values.append([])
        got = True
        continue
    try:
        values[-1].append([int(l[0]), int(l[-1])])
    except:continue

minn = 1e10
for i in values:minn=min(minn,len(i))

numt = len(values)
i = 0; last = -1
for i in range(minn):
    for j in values:
        if(last+1!=j[i][0]):print(last,j)
        last = j[i][1]

for i in range(minn):
    for j in values:print(j[i],end=', ')
    print()