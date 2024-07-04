#include <iostream>
#include <cassert>
#include "list.h"
using namespace lab618;

int main() {
    CDualLinkedList<int> list;
    int n = 1; // 4 3 2 1
    list.pushFront(n);
    ++n;
    list.pushFront(n);
    ++n;
    list.pushFront(n);
    ++n;
    list.pushFront(n);
    ++n;
    for (auto it = list.end(); it.isValid(); --it) {
        std::cout << list.getSize() << "\n"; //4
        list.eraseAndNext(it);
    }
    std::cout << list.getSize() << "\n"; // 0
    return 0;
}
