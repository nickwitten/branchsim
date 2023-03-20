import IPython
import subprocess
import os
import math
import sys

TRACE_DIR = "./traces"
traces = os.listdir("traces")
trace = sys.argv[1]

def predictor_size(P, L, N, G):
    yp_ht = P * (1 << L)
    yp_pt = 2 * (1 << P)
    perceptron = (math.ceil(math.log2(1.93*G + 14)) + 1) * (G + 1) * (1 << N)
    tourny = 1 << 14  # 2 KiB
    return yp_ht + yp_pt + perceptron + tourny

MAX_SIZE = 26 * 1024 * 8
MIN_P = 9
MIN_L = 9
MIN_N = 8
MIN_G = 32

MAX_P = MIN_P
while predictor_size(MAX_P + 1, MIN_L, MIN_N, MIN_G) <= MAX_SIZE:
    MAX_P += 1
MAX_L = MIN_L
while predictor_size(MIN_P, MAX_L + 1, MIN_N, MIN_G) <= MAX_SIZE:
    MAX_L += 1
MAX_N = MIN_N
while predictor_size(MIN_P, MIN_L, MAX_N + 1, MIN_G) <= MAX_SIZE:
    MAX_N += 1
MAX_G = 64

# for trace in traces:
with open(f"{trace}_results.txt", "w") as f:
    f.write(f"Evaluating {trace}\n")
    print(f"Evaluating {trace}")
for P in range(MIN_P, MAX_P + 1):
    for L in range(MIN_L, MAX_L + 1):
        for N in range(MIN_N, MAX_N + 1):
            for G in range(MIN_G, MAX_G + 1):
                for C in range(0, 4):
                    if predictor_size(P, L, N, G) <= MAX_SIZE:
                        with open(f"{trace}_results.txt", "a") as f:
                            trace_path = os.path.join(TRACE_DIR, trace)
                            # IPython.embed()
                            p1 = subprocess.Popen(['./branchsim', '-i', trace_path, '-M3', '-C', str(C), '-P', str(P), '-L', str(L), '-N', str(N), '-G', str(G)], stdout=subprocess.PIPE)
                            p2 = subprocess.Popen(['grep', 'accuracy'], stdin=p1.stdout, stdout=subprocess.PIPE)
                            accuracy = str(p2.stdout.read()).split(":")[1].strip().replace("\\n'", "")
                            print(f"{P}, {L}, {N}, {G}, {C}")
                            print(accuracy)
                            f.write(f"{P}, {L}, {N}, {G}, {C}\n")
                            f.write(accuracy + "\n")

