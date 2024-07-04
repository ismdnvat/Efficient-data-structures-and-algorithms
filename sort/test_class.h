#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

class Person {
 public:
    std::string name;
    int age = 0;
    float height = 0.f;
    float weight = 0.f;
    Person() = default;
    Person(std::string n, int a, float h, float w) : name(std::move(n)), age(a), height(h), weight(w) {}
    friend std::ostream& operator<<(std::ostream& os, const Person& person) {
        os << person.name << " " << person.age << " " << person.height << " " << person.weight << "\n";
        return os;
    }
};

// Сортировка по имени
int compareByName(const Person *pElem1, const Person *pElem2) {
    return pElem1->name < pElem2->name ? 1 : pElem1->name == pElem2->name ? 0 : -1;
}

// Сортировка по возрасту
int compareByAge(const Person *pElem1, const Person *pElem2) {
    return pElem1->age < pElem2->age ? 1 : pElem1->age == pElem2->age ? 0 : -1;
}

// Сортировка по росту
int compareByHeight(const Person *pElem1, const Person *pElem2) {
    return pElem1->height < pElem2->height ? 1 : pElem1->height == pElem2->height ? 0 : -1;
}

// Сортировка по весу
int compareByWeight(const Person *pElem1, const Person *pElem2) {
    return pElem1->weight < pElem2->weight ? 1 : pElem1->weight == pElem2->weight ? 0 : -1;
}
