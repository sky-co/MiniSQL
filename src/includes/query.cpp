// query.cpp
#include "query.hpp"
#include "globals.hpp"
#include "parser.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

Query::Query(Database* db)
    : dbptr(db) {}

Query::Query(std::unordered_map<std::string, Database>* dbs, std::string* currentDb)
    : databases(dbs)
    , currentDatabase(currentDb) {}

void Query::getQ() {
    userInput.clear();
    std::cout << "MiniSQL> ";
    if (inputFile.is_open()) {
        std::string line{};
        std::ostringstream queryStream{};
        while (std::getline(inputFile, line)) {
            queryStream << line << " ";
            if (line.find(';') != std::string::npos) {
                break;
            }
        }
        userInput = queryStream.str();
    } else {
        std::ostringstream queryStream{};
        std::string line{};
        while (std::getline(std::cin, line)) {
            queryStream << line << " ";
            if (line.find(';') != std::string::npos) {
                break;
            }
        }
        userInput = queryStream.str();
    }
    // Remove leading and trailing whitespace

    std::cout << "Processed user input: " << userInput << std::endl;
}

void Query::excQ() {
    Parser parser{};
    parser.parse(userInput, *databases, *currentDatabase);
}
