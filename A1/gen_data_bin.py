import os
import sys
import numpy as np
import struct

np.random.seed(42)

ii32 = np.iinfo(np.uint32)

def generate_test_set(nsize, p):
    print(f'generating data for {nsize} {p}')
    data = np.random.randint(ii32.max, dtype=np.uint32, size=nsize)
    infile = f'input_{nsize}.bin'

    with open(infile, 'wb') as fp:
        fp.write(struct.pack('Ii', nsize, p))
        for val in data:
            # print(val)
            fp.write(struct.pack('I', val))

    print(f'Sample data saved at {infile}')


if __name__ == '__main__':
    nsize = int(sys.argv[1])
    p = int(sys.argv[2])
    generate_test_set(nsize, p)