import numpy as np
import matplotlib.pyplot as plt

with open('../build/bin/time.txt', 'r') as file:
    lines = file.readlines()

data = np.array([list(map(int, line.split())) for line in lines])

time_10k = data[:3]
time_100k = data[3:6]
time_500k = data[6:9]
time_1m = data[9:12]

N_values = ['10.000', '100.000', '500.000', '1.000.000']

filling_struct_10k = time_10k[:, 0]
filling_struct_100k = time_100k[:, 0]
filling_struct_500k = time_500k[:, 0]
filling_struct_1m = time_1m[:, 0]

CAVLTree = [filling_struct_10k[0], filling_struct_100k[0], filling_struct_500k[0], filling_struct_1m[0]]
BinarySearch = [filling_struct_10k[1], filling_struct_100k[1], filling_struct_500k[1], filling_struct_1m[1]]
CHash = [filling_struct_10k[2], filling_struct_100k[2], filling_struct_500k[2], filling_struct_1m[2]]

plt.figure(figsize=(10, 6))

plt.plot(N_values, CAVLTree, label='CAVLTree', marker='o')
plt.plot(N_values, BinarySearch, label='BinarySearch', marker='o')
plt.plot(N_values, CHash, label='CHash', marker='o')

plt.title('Time Measurements for Different Data Sizes (Filling Struct)')
plt.xlabel('Number of Elements')
plt.ylabel('Time (ms)')
plt.legend()
plt.grid(True)
plt.savefig('filling_graph.png')
plt.close()


search_existing_10k = time_10k[:, 1]
search_existing_100k = time_100k[:, 1]
search_existing_500k = time_500k[:, 1]
search_existing_1m = time_1m[:, 1]

CAVLTree = [search_existing_10k[0], search_existing_100k[0], search_existing_500k[0], search_existing_1m[0]]
BinarySearch = [search_existing_10k[1], search_existing_100k[1], search_existing_500k[1], search_existing_1m[1]]
CHash = [search_existing_10k[2], search_existing_100k[2], search_existing_500k[2], search_existing_1m[2]]

plt.figure(figsize=(10, 6))

plt.plot(N_values, CAVLTree, label='CAVLTree', marker='o')
plt.plot(N_values, BinarySearch, label='BinarySearch', marker='o')
plt.plot(N_values, CHash, label='CHash', marker='o')

plt.title('Time Measurements for Different Data Sizes (Search Existing)')
plt.xlabel('Number of Elements')
plt.ylabel('Time (ms)')
plt.legend()
plt.grid(True)
plt.savefig('search_existing_graph.png')
plt.close()


search_random_10k = time_10k[:, 2]
search_random_100k = time_100k[:, 2]
search_random_500k = time_500k[:, 2]
search_random_1m = time_1m[:, 2]

CAVLTree = [search_random_10k[0], search_random_100k[0], search_random_500k[0], search_random_1m[0]]
BinarySearch = [search_random_10k[1], search_random_100k[1], search_random_500k[1], search_random_1m[1]]
CHash = [search_random_10k[2], search_random_100k[2], search_random_500k[2], search_random_1m[2]]

plt.figure(figsize=(10, 6))

plt.plot(N_values, CAVLTree, label='CAVLTree', marker='o')
plt.plot(N_values, BinarySearch, label='BinarySearch', marker='o')
plt.plot(N_values, CHash, label='CHash', marker='o')

plt.title('Time Measurements for Different Data Sizes (Random Existing)')
plt.xlabel('Number of Elements')
plt.ylabel('Time (ms)')
plt.legend()
plt.grid(True)
plt.savefig('search_random_graph.png')
plt.close()

deleting_10k = time_10k[:, 3]
deleting_100k = time_100k[:, 3]
deleting_500k = time_500k[:, 3]
deleting_1m = time_1m[:, 3]

CAVLTree = [deleting_10k[0], deleting_100k[0], deleting_500k[0], deleting_1m[0]]
BinarySearch = [deleting_10k[1], deleting_100k[1], deleting_500k[1], deleting_1m[1]]
CHash = [deleting_10k[2], deleting_100k[2], deleting_500k[2], deleting_1m[2]]

plt.figure(figsize=(10, 6))

plt.plot(N_values, CAVLTree, label='CAVLTree', marker='o')
plt.plot(N_values, BinarySearch, label='BinarySearch', marker='o')
plt.plot(N_values, CHash, label='CHash', marker='o')

plt.title('Time Measurements for Different Data Sizes (Search Delete)')
plt.xlabel('Number of Elements')
plt.ylabel('Time (ms)')
plt.legend()
plt.grid(True)
plt.savefig('deleting_graph.png')
plt.close()