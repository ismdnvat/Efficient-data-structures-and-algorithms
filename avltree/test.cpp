#include <iostream>
#include <cassert>
#include <chrono>
#include <fstream>
#include "avltree.h"

int compareInt(const int* a, const int* b)
{
    return *a - *b;
}

int main() {
    lab618::CAVLTree<int, compareInt> avlTree(10);
    std::ofstream outputFile("timer.txt");
    int i = 0;
    auto start = std::chrono::high_resolution_clock::now();
    while(++i < 1000000) {
        auto flag = avlTree.add(new int(i));
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    outputFile << "add: " << duration.count() << " milliseconds\n";
    i = 0;
    start = std::chrono::high_resolution_clock::now();
    while(++i < 1000000) {
        const int& k = i;
        auto flag = avlTree.find(k);
    }
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    outputFile << "find: " << duration.count() << " milliseconds\n";
    i = 1;
    start = std::chrono::high_resolution_clock::now();
    while(++i < 1000000) {
        auto flag = avlTree.update(new int(i));
    }
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    outputFile << "update: " << duration.count() << " milliseconds\n";
    i = 1;
    start = std::chrono::high_resolution_clock::now();
    while(++i < 1000000) {
        const int& k = i;
        auto flag = avlTree.remove(k);
    }
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    outputFile << "remove: " << duration.count() << " milliseconds\n";
    start = std::chrono::high_resolution_clock::now();
    avlTree.clear();
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    outputFile << "clear: " << duration.count() << " milliseconds\n";

    return 0;
}
