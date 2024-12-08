#include "database.hpp"
#include "globals.hpp"
#include "query.hpp"
#include <fstream>
#include <iostream>
#include <unordered_map>

int main(int argv, char* argc[]) {
    // input: MyMiniSQL input.sql output.csv
    if (argv != 3) {
        std::cout << "Please input the correct command" << std::endl;
        return 0;
    }

    std::string inputFilename = argc[1];
    std::string outputFilename = argc[2];
    inputFile.open(inputFilename);
    if (!inputFile || !outputFile) {
        std::cerr << "Cannot open the input file:" << inputFilename << std::endl;
        return 0;
    }

    outputFile.open(outputFilename);
    if (!outputFile) {
        std::cerr << "Cannot open the output file:" << outputFilename << std::endl;
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
    outputFile.close();

    return 0;
}
