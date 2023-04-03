import tempfile
import os
import sys
import time

if len(sys.argv) != 3:
    print(f"\nUsage: {sys.argv[0]} <n_byte> <time>\n\n\tWrite <n_byte> bytes from memory to a tmp_file <time> times, print used time to console.\n")
    exit(1)

fd, path = tempfile.mkstemp()
n_byte = int(sys.argv[1])
times = int(sys.argv[2])
with os.fdopen(fd, 'w') as tmp:
    buf = "6" * n_byte
    ctime = time.perf_counter()
    rtime = time.time()
    for i in range(times):
        tmp.write(buf)
    ctime = time.perf_counter() - ctime
    rtime = time.time() - rtime
    print(f"\nCPU time: {ctime} sec\nReal time: {rtime} sec\n")