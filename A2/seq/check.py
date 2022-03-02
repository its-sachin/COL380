from sys import argv
f1 = open(argv[1], 'r')
f2 = open(argv[2], 'r')

l1 = []
l2 = []
for l in f1.readlines():
    l1.append(l.strip('\n').split(','))
for l in f2.readlines():
    l2.append(l.strip('\n').split(','))

if(len(l1) != len(l2)):
    print('Error: unequal number of lines')

else:
    for i in range(len(l1)):
        if(len(l1[i]) != len(l2[i])):
            print(f'Error: unequal number of columns at {i}')
        else:
            for j in range(len(l1[i])):
                if(l1[i][j] != l2[i][j]):
                    print(f'Error: unequal value at {i}.{j}')
                    print(f'{l1[i][j]} != {l2[i][j]}')
                    break
    else:
        print('Equal')