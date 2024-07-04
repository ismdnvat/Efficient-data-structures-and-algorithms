#ifndef SORT_HEAD_H_2024_03_21
#define SORT_HEAD_H_2024_03_21

namespace templates
{
/** Определение типа функции сравнения элементов
\return
\li > 0  - pElem1 меньше pElem2
\li 0   - элементы pElem1 и pElem2 равны
\li < 0 - pElem1 больше pElem2
*/
typedef int (CompareSortType)(const void *pElem1, const void *pElem2);

void mergeSort(void **ppArray, int length, CompareSortType pCompareFunc);
void heapSort(void **ppArray, int length, CompareSortType pCompareFunc);
void quickSort(void** ppArray, int length, CompareSortType pCompareFunc);

template <class T>
void mergeSort(T **ppArray, int length, int (pCompareFunc)(const T *pElem1, const T *pElem2))
{
    mergeSort(reinterpret_cast<void**>(ppArray), length, (CompareSortType*)pCompareFunc);
}
template <class T>
void heapSort(T **ppArray, int length, int (pCompareFunc)(const T *pElem1, const T *pElem2))
{
    heapSort(reinterpret_cast<void**>(ppArray), length, (CompareSortType*)pCompareFunc);
}

template <class T>
void quickSort(T** ppArray, int length, int (pCompareFunc)(const T* pElem1, const T* pElem2))
{
    quickSort(reinterpret_cast<void**>(ppArray), length, (CompareSortType*)pCompareFunc);
}

static void merge(void **ppArray, int left, int middle, int right, CompareSortType pCompareFunc);
static void mergeSortRecursive(void **ppArray, int left, int right, CompareSortType pCompareFunc);
void mergeSort(void **ppArray, int length, CompareSortType pCompareFunc);
void heapify(void **ppArray, int length, int i, CompareSortType pCompareFunc);
void heapSort(void **ppArray, int length, CompareSortType pCompareFunc);
void swap(void** a, void** b);
void quickSort(void** ppArray, int length, CompareSortType pCompareFunc);


}; // namespace templates

#endif // #define SORT_HEAD_H_2024_03_21
