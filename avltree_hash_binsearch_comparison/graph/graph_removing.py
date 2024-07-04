import numpy as np
import matplotlib.pyplot as plt

with open('../build/bin/time2.txt', 'r') as file:
    numbers = list(map(int, file.readline().split()))

CAVLTree = []
CHash = []
for i, num in enumerate(numbers):
    if i % 2 == 0:
        CAVLTree.append(num)
    else:
        CHash.append(num)
N_values = ['10.000', '100.000', '500.000', '1.000.000']

plt.figure(figsize=(10, 6))

plt.plot(N_values, CAVLTree, label='CAVLTree', marker='o')
plt.plot(N_values, CHash, label='CHash', marker='o')

plt.title('Time Measurements for Different Data Sizes (Removing Struct)')
plt.xlabel('Number of Elements')
plt.ylabel('Time (ms)')
plt.legend()
plt.grid(True)
plt.savefig('removing_by_elements_graph.png')
plt.close()