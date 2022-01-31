from matplotlib import pyplot as plt


# 25
v = [3,5,7,10,12]
# varying p
# f = open('output/varyingp.sh.o2630050')
# vals = []
# for i in f.readlines():
#     l = i.strip('\n').split(' ')
#     if(l[0] == 'Time'):vals.append(float(l[-1][:-2])/1000)

# th = [i for i in range(1,11)]
# for i in range(0,35,10):
#     plt.plot(th, vals[i:i+10], marker = 'o',label=f'p = {v[i//10]}')

# plt.grid(b = True, color ='grey', linestyle ='-.', linewidth = 0.5, alpha = 0.2)
# plt.legend(loc="upper right")
# plt.title('Varying p')
# plt.xlabel('# of threads')
# plt.ylabel('Time (s)')
# plt.show()

# th = [i for i in range(1,15)]
# for i in v:
#     f = open(f'output/run_code25-{i}.txt')
#     vals = []
#     for w in f.readlines():
#         l = w.strip('\n').split(' ')
#         if(l[0] == 'Time'):vals.append(float(l[-1][:-2])/1000)
#     print(vals)
#     plt.plot(th, vals[:14], marker = 'o',label=f'# cpu = {i}')

# plt.grid(b = True, color ='grey', linestyle ='-.', linewidth = 0.5, alpha = 0.2)
# plt.legend(loc="upper right")
# plt.title('Varying # of cpu')
# plt.xlabel('# of threads')
# plt.ylabel('Time (s)')
# plt.show()

th = [i for i in range(1,13)]
aa = [14,16,17,18,19,20,22,23,24,25,26,27]
vals = []
for i in aa:
    f = open(f'output/run25.sh.o26305{i}')
    for w in f.readlines():
        l = w.strip('\n').split(' ')
        if(l[0] == 'Time'):vals.append(float(l[-1][:-2])/1000)
plt.plot(th, vals, marker = 'o')
print(vals)
plt.grid(b = True, color ='grey', linestyle ='-.', linewidth = 0.5, alpha = 0.2)
plt.title('# of CPU VS Time')
plt.xlabel('# of CPU')
plt.ylabel('Time (s)')
plt.show()


# 32
# d32_c10 = [2.80719e+06,  1.44714e+06, 971654, 740358, 590820, 511283,  429932, 381277, 354947, 295301]
# d32_c5  = [2.78313e+06, 1.44567e+06, 1.00617e+06, 774794, 597219, 578378, 569475, 565341]
# for i in range(len(d32_c10)):d32_c10[i]//=1000
# for i in range(len(d32_c5)):d32_c5[i]//=1000

# plt.plot([i for i in range(1,11)],d32_c10, marker = 'o',label=f'# cpu = {10}')
# # plt.plot(d32_c5, marker = 'o',label=f'# cpu = {5}')
# plt.grid(b = True, color ='grey', linestyle ='-.', linewidth = 0.5, alpha = 0.2)
# # plt.legend(loc="upper right")
# plt.title('# of CPU VS Time (2^32 size)')
# plt.xlabel('# of CPU')
# plt.ylabel('Time (s)')
# plt.show()