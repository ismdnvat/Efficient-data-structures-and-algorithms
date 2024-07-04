#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <random>
#include <sstream>

struct Credentials {
    std::string login;
    std::string password;
};

std::string generateRandomString(int minLength, int maxLength) {
    static const std::string charset =
        "abcdefghijklmnopqrstuvwxyz"
//        "абвгдеёжзийклмнопрстуфхцчшщъыьэюя"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
//        "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"
        "0123456789";

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> lengthDistribution(minLength, maxLength);
    std::uniform_int_distribution<> charDistribution(0, charset.size() - 1);

    int length = lengthDistribution(generator);
    std::string result;
    result.reserve(length);
    for (int i = 0; i < length; ++i) {
        result += charset[charDistribution(generator)];
    }
    return result;
}

void generateAndWriteCredentialsToFile(int N, int minLength, int maxLength, const std::string& filename) {
    std::ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return;
    }

    std::unordered_set<std::string> uniqueCredentials;
    while (uniqueCredentials.size() < N) {
        std::string login = generateRandomString(minLength, maxLength);
        std::string password = generateRandomString(minLength, maxLength);
        std::stringstream ss;
        ss << login << " " << password;
        std::string credential = ss.str();
        if (uniqueCredentials.insert(credential).second) {
            outputFile << credential << std::endl;
        }
    }

    outputFile.close();
}

int main(int argc, char* argv[]) {
    int N = 10000;
    if (argc == 2) {
        N = std::atoi(argv[1]);
    }
    int minLength = 7;
    int maxLength = 20;
    std::string filename = "data.txt";
    generateAndWriteCredentialsToFile(N, minLength, maxLength, filename);
    filename = "search_data.txt";
    generateAndWriteCredentialsToFile(2 * N, minLength, maxLength, filename);
    return 0;
}
