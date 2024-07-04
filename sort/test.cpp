#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "sort.h"
#include "sort.cpp"
#include "test_class.h"
#include <iostream>

#define N 100000

using namespace templates;

// Функция для создания случайного имени
std::string getRandomName() {
    static const char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(5, 10);

    std::string name;
    int length = dis(gen);
    for (int i = 0; i < length; ++i) {
        name += alphabet[dis(gen) % (sizeof(alphabet) - 1)];
    }
    return name;
}

// Функция для создания массива случайных объектов Person
void getRandomPersons(Person *person, int size) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> ageDis(18, 80);
    static std::uniform_int_distribution<> heightDis(150, 200);
    static std::uniform_int_distribution<> weightDis(50, 150);
    for (int i = 0; i < size; ++i) {
        person[i] = Person(getRandomName(), ageDis(gen), heightDis(gen), weightDis(gen));
    }
}

template <typename T>
bool isSorted(T **ppArray, int size, int (*pCompareFunc)(const T *pElem1, const T *pElem2)) {
    for (int i = 0; i < size - 1; ++i) {
        if (pCompareFunc(ppArray[i], ppArray[i + 1]) < 0) {
//            std::cout << *ppArray[i] << " " << *ppArray[i + 1] <<  " " << "\n";
            return false;
        }
    }
    return true;
}

template <typename T>
void Print(T **ppArray, int size) {
    for (int i = 0; i < size; ++i) {
        std::cout << *ppArray[i] << " ";
    }
    std::cout << "\n";
}


TEST_CASE("Sorting Persons by MergeSort") {
    SUBCASE("Sorting by Name") {
        Person persons[N];
        getRandomPersons(persons, N);
        Person *persons_ptr[N];
        for (int i = 0; i < N; ++i) {
            persons_ptr[i] = &persons[i];
        }
        mergeSort(persons_ptr, N, compareByName);
        CHECK(isSorted(persons_ptr, N, compareByName));
    }

    SUBCASE("Sorting by Age") {
        Person persons[N];
        getRandomPersons(persons, N);
        Person *persons_ptr[N];
        for (int i = 0; i < N; ++i) {
            persons_ptr[i] = &persons[i];
        }
        mergeSort(persons_ptr, N, compareByAge);
        CHECK(isSorted(persons_ptr, N, compareByAge));
    }

    SUBCASE("Sorting by Height") {
        Person persons[N];
        getRandomPersons(persons, N);
        Person *persons_ptr[N];
        for (int i = 0; i < N; ++i) {
            persons_ptr[i] = &persons[i];
        }
        mergeSort(persons_ptr, N, compareByHeight);
        CHECK(isSorted(persons_ptr, N, compareByHeight));

    }

    SUBCASE("Sorting by Weight") {
        Person persons[N];
        getRandomPersons(persons, N);
        Person *persons_ptr[N];
        for (int i = 0; i < N; ++i) {
            persons_ptr[i] = &persons[i];
        }
        mergeSort(persons_ptr, N, compareByWeight);
        CHECK(isSorted(persons_ptr, N, compareByWeight));
    }
}

TEST_CASE("Sorting Sorted Persons by MergeSort") {
    SUBCASE("Sorting by Name") {
        Person persons[N];
        getRandomPersons(persons, N);
        Person *persons_ptr[N];
        for (int i = 0; i < N; ++i) {
            persons_ptr[i] = &persons[i];
        }
        std::sort(std::begin(persons_ptr), std::end(persons_ptr), [](Person* a, Person* b) {
            return a->name < b->name;
        });
        mergeSort(persons_ptr, N, compareByName);
        CHECK(isSorted(persons_ptr, N, compareByName));
    }

    SUBCASE("Sorting by Age") {
        Person persons[N];
        getRandomPersons(persons, N);
        Person *persons_ptr[N];
        for (int i = 0; i < N; ++i) {
            persons_ptr[i] = &persons[i];
        }
        std::sort(std::begin(persons_ptr), std::end(persons_ptr), [](Person* a, Person* b) {
            return a->age < b->age;
        });
        mergeSort(persons_ptr, N, compareByAge);
        CHECK(isSorted(persons_ptr, N, compareByAge));
    }

    SUBCASE("Sorting by Height") {
        Person persons[N];
        getRandomPersons(persons, N);
        Person *persons_ptr[N];
        for (int i = 0; i < N; ++i) {
            persons_ptr[i] = &persons[i];
        }
        std::sort(std::begin(persons_ptr), std::end(persons_ptr), [](Person* a, Person* b) {
            return a->height < b->height;
        });
        mergeSort(persons_ptr, N, compareByHeight);
        CHECK(isSorted(persons_ptr, N, compareByHeight));
    }

    SUBCASE("Sorting by Weight") {
        Person persons[N];
        getRandomPersons(persons, N);
        Person *persons_ptr[N];
        for (int i = 0; i < N; ++i) {
            persons_ptr[i] = &persons[i];
        }
        std::sort(std::begin(persons_ptr), std::end(persons_ptr), [](Person* a, Person* b) {
            return a->weight < b->weight;
        });
        mergeSort(persons_ptr, N, compareByWeight);
        CHECK(isSorted(persons_ptr, N, compareByWeight));
    }
}

TEST_CASE("Sorting Persons by HeapSort") {
    SUBCASE("Sorting by Name") {
        Person persons[N];
        getRandomPersons(persons, N);
        Person *persons_ptr[N];
        for (int i = 0; i < N; ++i) {
            persons_ptr[i] = &persons[i];
        }
        heapSort(persons_ptr, N, compareByName);
        CHECK(isSorted(persons_ptr, N, compareByName));
    }

    SUBCASE("Sorting by Age") {
        Person persons[N];
        getRandomPersons(persons, N);
        Person *persons_ptr[N];
        for (int i = 0; i < N; ++i) {
            persons_ptr[i] = &persons[i];
        }
        heapSort(persons_ptr, N, compareByAge);
        CHECK(isSorted(persons_ptr, N, compareByAge));
    }

    SUBCASE("Sorting by Height") {
        Person persons[N];
        getRandomPersons(persons, N);
        Person *persons_ptr[N];
        for (int i = 0; i < N; ++i) {
            persons_ptr[i] = &persons[i];
        }
        heapSort(persons_ptr, N, compareByHeight);
        CHECK(isSorted(persons_ptr, N, compareByHeight));
    }

    SUBCASE("Sorting by Weight") {
        Person persons[N];
        getRandomPersons(persons, N);
        Person *persons_ptr[N];
        for (int i = 0; i < N; ++i) {
            persons_ptr[i] = &persons[i];
        }
        heapSort(persons_ptr, N, compareByWeight);
        CHECK(isSorted(persons_ptr, N, compareByWeight));
    }
}

TEST_CASE("Sorting Sorted Persons by HeapSort") {
    SUBCASE("Sorting by Name") {
        Person persons[N];
        getRandomPersons(persons, N);
        Person *persons_ptr[N];
        for (int i = 0; i < N; ++i) {
            persons_ptr[i] = &persons[i];
        }
        std::sort(std::begin(persons_ptr), std::end(persons_ptr), [](Person* a, Person* b) {
            return a->name < b->name;
        });
        heapSort(persons_ptr, N, compareByName);
        CHECK(isSorted(persons_ptr, N, compareByName));
    }

    SUBCASE("Sorting by Age") {
        Person persons[N];
        getRandomPersons(persons, N);
        Person *persons_ptr[N];
        for (int i = 0; i < N; ++i) {
            persons_ptr[i] = &persons[i];
        }
        std::sort(std::begin(persons_ptr), std::end(persons_ptr), [](Person* a, Person* b) {
            return a->age < b->age;
        });
        heapSort(persons_ptr, N, compareByAge);
        CHECK(isSorted(persons_ptr, N, compareByAge));
    }

    SUBCASE("Sorting by Height") {
        Person persons[N];
        getRandomPersons(persons, N);
        Person *persons_ptr[N];
        for (int i = 0; i < N; ++i) {
            persons_ptr[i] = &persons[i];
        }
        std::sort(std::begin(persons_ptr), std::end(persons_ptr), [](Person* a, Person* b) {
            return a->height < b->height;
        });
        heapSort(persons_ptr, N, compareByHeight);
        CHECK(isSorted(persons_ptr, N, compareByHeight));
    }

    SUBCASE("Sorting by Weight") {
        Person persons[N];
        getRandomPersons(persons, N);
        Person *persons_ptr[N];
        for (int i = 0; i < N; ++i) {
            persons_ptr[i] = &persons[i];
        }
        std::sort(std::begin(persons_ptr), std::end(persons_ptr), [](Person* a, Person* b) {
            return a->weight < b->weight;
        });
        heapSort(persons_ptr, N, compareByWeight);
        CHECK(isSorted(persons_ptr, N, compareByWeight));
    }
}

TEST_CASE("Sorting Persons by quickSort") {
    SUBCASE("Sorting by Name") {
        Person persons[N];
        getRandomPersons(persons, N);
        Person *persons_ptr[N];
        for (int i = 0; i < N; ++i) {
            persons_ptr[i] = &persons[i];
        }
        quickSort(persons_ptr, N, compareByName);
        CHECK(isSorted(persons_ptr, N, compareByName));
    }

    SUBCASE("Sorting by Age") {
        Person persons[N];
        getRandomPersons(persons, N);
        Person *persons_ptr[N];
        for (int i = 0; i < N; ++i) {
            persons_ptr[i] = &persons[i];
        }
        quickSort(persons_ptr, N, compareByAge);
        CHECK(isSorted(persons_ptr, N, compareByAge));
    }

    SUBCASE("Sorting by Height") {
        Person persons[N];
        getRandomPersons(persons, N);
        Person *persons_ptr[N];
        for (int i = 0; i < N; ++i) {
            persons_ptr[i] = &persons[i];
        }
        quickSort(persons_ptr, N, compareByHeight);
        CHECK(isSorted(persons_ptr, N, compareByHeight));
    }

    SUBCASE("Sorting by Weight") {
        Person persons[N];
        getRandomPersons(persons, N);
        Person *persons_ptr[N];
        for (int i = 0; i < N; ++i) {
            persons_ptr[i] = &persons[i];
        }
        quickSort(persons_ptr, N, compareByWeight);
        CHECK(isSorted(persons_ptr, N, compareByWeight));
    }
}

TEST_CASE("Sorting sorted Persons by quickSort") {
    SUBCASE("Sorting by Name") {
        Person persons[N];
        getRandomPersons(persons, N);
        Person *persons_ptr[N];
        for (int i = 0; i < N; ++i) {
            persons_ptr[i] = &persons[i];
        }
        std::sort(std::begin(persons_ptr), std::end(persons_ptr), [](Person* a, Person* b) {
            return a->name < b->name;
        });
        quickSort(persons_ptr, N, compareByName);
        CHECK(isSorted(persons_ptr, N, compareByName));
    }

    SUBCASE("Sorting by Age") {
        Person persons[N];
        getRandomPersons(persons, N);
        Person *persons_ptr[N];
        for (int i = 0; i < N; ++i) {
            persons_ptr[i] = &persons[i];
        }
        std::sort(std::begin(persons_ptr), std::end(persons_ptr), [](Person* a, Person* b) {
            return a->age < b->age;
        });
        quickSort(persons_ptr, N, compareByAge);
        CHECK(isSorted(persons_ptr, N, compareByAge));
    }

    SUBCASE("Sorting by Height") {
        Person persons[N];
        getRandomPersons(persons, N);
        Person *persons_ptr[N];
        for (int i = 0; i < N; ++i) {
            persons_ptr[i] = &persons[i];
        }
        std::sort(std::begin(persons_ptr), std::end(persons_ptr), [](Person* a, Person* b) {
            return a->height < b->height;
        });
        quickSort(persons_ptr, N, compareByHeight);
        CHECK(isSorted(persons_ptr, N, compareByHeight));
    }

    SUBCASE("Sorting by Weight") {
        Person persons[N];
        getRandomPersons(persons, N);
        Person *persons_ptr[N];
        for (int i = 0; i < N; ++i) {
            persons_ptr[i] = &persons[i];
        }
        std::sort(std::begin(persons_ptr), std::end(persons_ptr), [](Person* a, Person* b) {
            return a->weight < b->weight;
        });
        quickSort(persons_ptr, N, compareByWeight);
        CHECK(isSorted(persons_ptr, N, compareByWeight));
    }
}
