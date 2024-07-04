import sys
import numpy as np
import matplotlib.pyplot as plt

def main():
    if len(sys.argv) != 3:
        print("Usage: python graph.py <file1> <file2>")
        return

    file1 = sys.argv[1]
    file2 = sys.argv[2]

    with open(file1, 'r') as f:
        times_mm = [float(line.strip()) for line in f]

    with open(file2, 'r') as f:
        times_new_delete = [float(line.strip()) for line in f]

    methods = ['add', 'find', 'update', 'remove']
    classes = ['CAVLTree with MemoryManager', 'CAVLTree with new/delete']
    colors = ['blue', 'orange']

    fig, ax = plt.subplots(figsize=(12, 8))

    bar_width = 0.35
    index = np.arange(len(methods)) * 2

    for i, class_name in enumerate(classes):
        times = times_mm if i == 0 else times_new_delete
        ax.bar(index + i * bar_width, times, bar_width, label=class_name, color=colors[i])

    ax.set_xlabel('Operation')
    ax.set_ylabel('Time (milliseconds)')
    ax.set_title('Time taken for operations')
    ax.set_xticks(index + bar_width / 2)
    ax.set_xticklabels(methods)
    ax.legend()
    plt.savefig('histogram.png')

if __name__ == "__main__":
    main()
