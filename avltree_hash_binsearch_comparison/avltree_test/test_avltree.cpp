#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <vector>
#include <sstream>
#include "avltree.h"

struct Credentials {
    std::string login;
    std::string password;
    Credentials() : login(""), password("") {}
    Credentials(std::string& login, std::string& password) : login(login), password(password) {}
};

int32_t Compare(const Credentials* pElement1, const Credentials* pElement2) {
    if (pElement1->login < pElement2->login) {
        return -1;
    } else if (pElement1->login > pElement2->login) {
        return 1;
    } else {
        if (pElement1->password < pElement2->password) {
            return -1;
        } else if (pElement1->password > pElement2->password) {
            return 1;
        } else {
            return 0;
        }
    }
}

void readCredentialsFromFile(const std::string& filename, std::vector<Credentials>& credentials) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open file!" << std::endl;
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

void findCredentialsInAvltreeTable(lab618::CAVLTree<Credentials, &Compare>& avltreeTable, const std::vector<Credentials>& credentials, std::ofstream& outFile) {
    if (!outFile.is_open()) {
        std::cerr << "Unable to open file for writing!" << std::endl;
        return;
    }
    auto start = std::chrono::high_resolution_clock::now();
    for (auto& creds : credentials) {
        auto flag = avltreeTable.find(creds);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    outFile << duration << " ";
}

void deleteCredentialsInAvltreeTable(lab618::CAVLTree<Credentials, &Compare>& avltreeTable, const std::vector<Credentials>& credentials, std::ofstream& outFile) {
    if (!outFile.is_open()) {
        std::cerr << "Unable to open file for writing!" << std::endl;
        return;
    }
    auto start = std::chrono::high_resolution_clock::now();
    for (auto& creds : credentials) {
        auto flag = avltreeTable.remove(creds);
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
        std::cerr << "Unable to open file!" << std::endl;
        return 1;
    }
    const int blockSize = 1024;
    lab618::CAVLTree<Credentials, Compare> avltree(blockSize);
    std::vector<Credentials> credentials;
    credentials.reserve(N);
    readCredentialsFromFile("data.txt", credentials);
    // добавление элементов в хеш таблицу
    auto startTime = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < credentials.size(); ++i) {
        avltree.add(&credentials[i]);
    }
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    // поиск тех же элементов в хеш таблице
    file << duration << " ";
    findCredentialsInAvltreeTable(avltree, credentials, file);
    // поиск случайных элементов в хеш таблице
    std::vector<Credentials> search_credentials;
    search_credentials.reserve(2 * N);
    readCredentialsFromFile("search_data.txt", search_credentials);
    findCredentialsInAvltreeTable(avltree, search_credentials, file);
    startTime = std::chrono::high_resolution_clock::now();
    avltree.clear();
    endTime = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    file << duration << "\n";
    file.close();
    std::ofstream file_del("time2.txt", std::ios::app);
    if (!file_del.is_open()) {
        std::cerr << "Unable to open file for writing delete !" << std::endl;
        return 1;
    }
    for (size_t i = 0; i < credentials.size(); ++i) {
        avltree.add(&credentials[i]);
    }
    deleteCredentialsInAvltreeTable(avltree, credentials, file_del);
    file_del.close();
    return 0;
}