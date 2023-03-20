import matplotlib.pyplot as plt
import os
import numpy as np

RESULTS_DIR = "./results"
FNAMES = os.listdir(RESULTS_DIR)

RESULTS_SIZE = 4432
results = {}
for fname in FNAMES:
    with open(os.path.join(RESULTS_DIR, fname)) as f:
        results[fname] = np.empty((RESULTS_SIZE, 6), dtype=np.float64)
        text = f.readlines()
        results[fname][:, 0:5] = np.array([row.split(", ") for row in text[1::2]], dtype=np.float64)
        results[fname][:, 5] = text[2::2]

av_results = np.empty((len(FNAMES), RESULTS_SIZE, 6), dtype=np.float64)
for i, fname in enumerate(FNAMES):
    av_results[i] = results[fname]
av_results = np.mean(av_results, axis=0)
best_row = av_results[np.argmax(av_results[:,5])]

params = ['P', 'L', 'N', 'G', 'C']
for i, param in enumerate(params):
    mask = np.array([True] * RESULTS_SIZE)
    for j in range(0, 5):
        if j != i:
            mask = mask & (av_results[:, j] == best_row[j])
    plt.subplot(231 + i)
    plt.plot(av_results[mask][:, i], av_results[mask][:, 5])
    plt.ylabel("Average Accuracy")
    plt.title(f"Varying {param}")
plt.tight_layout()
plt.show()
print(best_row)
