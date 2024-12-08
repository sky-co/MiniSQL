#include "database.hpp"
#include "globals.hpp"
#include "query.hpp"
#include <fstream>
#include <iostream>
#include <unordered_map>

int main(int argv, char* argc[]) {
    // input: MyMiniSQL input.sql
    if (argv != 2) {
        std::cout << "Please input the correct command" << std::endl;
        return 0;
    }

    std::string inputFilename = argc[1];
    inputFile.open(inputFilename);
    if (!inputFile) {
        std::cerr << "Cannot open the input file:" << inputFilename << std::endl;
        return 0;
    }

    std::unordered_map<std::string, Database> databases{};
    std::string currentDatabase{};
    std::cout << ">_< Welcome to MiniSQL" << std::endl;
    Query query(&databases, &currentDatabase);
    while (1) {
        query.getQ();
        query.excQ();
        if (inputFile.eof()) {
            break;
        }
    }
    for (auto& [name, db] : databases) {
        db.save(name + ".txt");
    }
    inputFile.close();

    return 0;
}
