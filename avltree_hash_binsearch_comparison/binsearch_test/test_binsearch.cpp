#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <vector>
#include <sstream>
#include <cstdlib>
#include "sort.h"
#include <algorithm>

using namespace templates;

struct Credentials {
    std::string login;
    std::string password;
    Credentials() : login(""), password("") {}
    Credentials(std::string& login, std::string& password) : login(login), password(password) {}
};

int Compare(const Credentials* pElement1, const Credentials* pElement2) {
    if (pElement1->login < pElement2->login) {
        return -1;
    } else if (pElement1->login > pElement2->login) {
        return 1;
    } else {
        if (pElement1->password < pElement2->password) {
            return -1;
        } else if (pElement1->password > pElement2->password) {
            return 1;
        }
        return 0;
    }
}

void readCredentialsFromFile(const std::string& filename, Credentials *ppArray, int size) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open file!" << std::endl;
        return;
    }

    std::string line;
    for (int i = 0; i < size; ++i) {
        if (!std::getline(file, line)) {
            std::cerr << "Error reading file!" << std::endl;
            return;
        }

        std::istringstream iss(line);
        std::string login, password;
        if (!(iss >> login >> password)) {
            std::cerr << "Error parsing line " << i + 1 << std::endl;
            return;
        }
        ppArray[i] = Credentials(login, password);
    }
    file.close();
}

void readCredentialsFromFileToVector(const std::string& filename, std::vector<Credentials>& credentials) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open file   ! " << filename << std::endl;
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        Credentials creds;
        std::istringstream iss(line);
        if (!(iss >> creds.login >> creds.password)) {
            continue;
        }
        credentials.push_back(creds);
    }
    file.close();
}

int binarySearch(Credentials** ppArray, int length, const Credentials* key, int (*compare)(const Credentials*, const Credentials*)) {
    int left = 0;
    int right = length - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = compare(key, ppArray[mid]);

        if (cmp == 0) {
            return mid;
        } else if (cmp < 0) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return -1; // Элемент не найден
}


void findCredentialsInArray(Credentials** ppArray, int length, const std::vector<Credentials>& credentials,  int (*compare)(const Credentials*, const Credentials*), std::ofstream& outFile) {
    if (!outFile.is_open()) {
        std::cerr << "Unable to open file for writing!" << std::endl;
        return;
    }
    auto start = std::chrono::high_resolution_clock::now();
    for (const auto& creds : credentials) {
        int index = binarySearch(ppArray, length, &creds, compare);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    outFile << duration << " ";
}

int main(int argc, char* argv[]) {
    int N = 10000;
    if (argc == 2) {
        N = std::atoi(argv[1]);
    }
    std::ofstream file("time.txt", std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Unable to open file!, " << "time.txt" << std::endl;
        return 1;
    }
    std::vector<Credentials> pData(N);
    readCredentialsFromFile("data.txt", pData.data(), N);
    std::vector<Credentials*> credentials(N);
    for (int i = 0; i < N; ++i) {
        credentials[i] = &pData[i];
    }
    auto startTime = std::chrono::high_resolution_clock::now();
    quickSort(credentials.data(), N, Compare);
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    file << duration << " ";

// поиск тех же элементов в хеш таблице
    std::vector<Credentials> credentials_in_vec;
    credentials_in_vec.reserve(N);
    readCredentialsFromFileToVector("search_data.txt", credentials_in_vec);
    findCredentialsInArray(credentials.data(), N, credentials_in_vec, Compare, file);

    // поиск случайных элементов в хеш таблице
    std::vector<Credentials> search_credentials;
    search_credentials.reserve(2 * N);
    readCredentialsFromFileToVector("search_data.txt", search_credentials);
    findCredentialsInArray(credentials.data(), N, search_credentials, Compare, file);
    startTime = std::chrono::high_resolution_clock::now();
    credentials.clear();
    endTime = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    file << duration << "\n";
    file.close();
    return 0;
}