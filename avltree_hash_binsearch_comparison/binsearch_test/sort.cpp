//#include "sort.h"
//
//using namespace templates;
//static void merge(void **ppArray, int left, int middle, int right, CompareSortType pCompareFunc) {
//    int i, j, k;
//    int n1 = middle - left + 1;
//    int n2 = right - middle;
//    void *LeftArray[n1];
//    void *RightArray[n2];
//    for (i = 0; i < n1; i++) {
//        LeftArray[i] = ppArray[left + i];
//    }
//    for (j = 0; j < n2; j++) {
//        RightArray[j] = ppArray[middle + 1 + j];
//    }
//    i = 0;
//    j = 0;
//    k = left;
//    while (i < n1 && j < n2) {
//        if (pCompareFunc(LeftArray[i], RightArray[j]) >= 0) {
//            ppArray[k] = LeftArray[i];
//            i++;
//        } else {
//            ppArray[k] = RightArray[j];
//            j++;
//        }
//        k++;
//    }
//    while (i < n1) {
//        ppArray[k] = LeftArray[i];
//        i++;
//        k++;
//    }
//    while (j < n2) {
//        ppArray[k] = RightArray[j];
//        j++;
//        k++;
//    }
//}
//
//static void mergeSortRecursive(void **ppArray, int left, int right, CompareSortType pCompareFunc) {
//    if (left < right) {
//        int middle = left + (right - left) / 2;
//        mergeSortRecursive(ppArray, left, middle, pCompareFunc);
//        mergeSortRecursive(ppArray, middle + 1, right, pCompareFunc);
//        merge(ppArray, left, middle, right, pCompareFunc);
//    }
//}
//
//void mergeSort(void **ppArray, int length, CompareSortType pCompareFunc) {
//    mergeSortRecursive(ppArray, 0, length - 1, pCompareFunc);
//}
//
//
//void heapify(void **ppArray, int length, int i, CompareSortType pCompareFunc) {
//    int largest = i;
//    int left = 2 * i + 1;
//    int right = 2 * i + 2;
//
//    if (left < length && pCompareFunc(ppArray[left], ppArray[largest]) <= 0) {
//        largest = left;
//    }
//    if (right < length && pCompareFunc(ppArray[right], ppArray[largest]) <= 0) {
//        largest = right;
//    }
//    if (largest != i) {
//        auto copy = ppArray[i];
//        ppArray[i] = ppArray[largest];
//        ppArray[largest] = copy;
//        heapify(ppArray, length, largest, pCompareFunc);
//    }
//}
//
//void heapSort(void **ppArray, int length, CompareSortType pCompareFunc) {
//    for (int i = length / 2 - 1; i >= 0; i--) {
//        heapify(ppArray, length, i, pCompareFunc);
//    }
//    for (int i = length - 1; i > 0; i--) {
//        auto copy = ppArray[0];
//        ppArray[0] = ppArray[i];
//        ppArray[i] = copy;
//        heapify(ppArray, i, 0, pCompareFunc);
//    }
//}
//
//void swap(void** a, void** b) {
//    void* temp = *a;
//    *a = *b;
//    *b = temp;
//}
//
//void quickSort(void** ppArray, int length, CompareSortType pCompareFunc) {
//    auto pivot = ppArray[length / 2];
//    int i = 0;
//    int j = length - 1;
//    do {
//        while (pCompareFunc(ppArray[i], pivot) > 0) {
//            ++i;
//        }
//        while (pCompareFunc(ppArray[j], pivot) < 0) {
//            --j;
//        }
//        if (i <= j) {
//            swap(&ppArray[i], &ppArray[j]);
//            i++;
//            j--;
//        }
//    } while (i <= j);
//    if (j > 0) {
//        quickSort(ppArray, j + 1, pCompareFunc);
//    }
//    if (i < length) {
//        quickSort(&ppArray[i], length - i, pCompareFunc);
//    }
//}