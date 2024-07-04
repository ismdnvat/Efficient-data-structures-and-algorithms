#include <iostream>
#include <cassert>
#include <chrono>
#include <fstream>
#include "avl_new_delete.h"
int compareInt(const int* a, const int* b)
{
    return *a - *b;
}

int main() {
    lab618::CAVLTree<int, compareInt> avlTree;
    std::ofstream outputFile("timer_new_delete.txt");
    std::ofstream timerFile("timer_for_graph_new_delete.txt");
    int i = 0;
    auto start = std::chrono::high_resolution_clock::now();
    while(++i < 1000000) {
        auto flag = avlTree.add(new int(i));
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    outputFile << "add: " << duration.count() << " milliseconds\n";
    timerFile << duration.count() << "\n";
    i = 0;
    start = std::chrono::high_resolution_clock::now();
    while(++i < 1000000) {
        const int& k = i;
        auto flag = avlTree.find(k);
    }
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    outputFile << "find: " << duration.count() << " milliseconds\n";
    timerFile << duration.count() << "\n";
    i = 1;
    start = std::chrono::high_resolution_clock::now();
    while(++i < 1000000) {
        auto flag = avlTree.update(new int(i));
    }
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    outputFile << "update: " << duration.count() << " milliseconds\n";
    timerFile << duration.count() << "\n";
    i = 0;
    start = std::chrono::high_resolution_clock::now();
    while(++i < 1000000) {
        const int& k = i;
        auto flag = avlTree.remove(k);
    }
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    outputFile << "remove: " << duration.count() << " milliseconds\n";
    timerFile << duration.count() << "\n";
    avlTree.clear();
    return 0;
}
