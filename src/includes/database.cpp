// database.cpp
#include "database.hpp"
#include <fstream>
#include <iostream>

void Database::createTable(const std::string& name, Table& table) {
    if (tables.find(name) == tables.end()) {
        tables[name] = std::move(table);
        std::cout << "Table " << name << " created." << std::endl;
    } else {
        std::cout << "Table " << name << " already exists." << std::endl;
    }
}

void Database::dropTable(const std::string& name) {
    if (tables.erase(name)) {
        std::cout << "Table " << name << " dropped." << std::endl;
    } else {
        std::cout << "Table " << name << " does not exist." << std::endl;
    }
}

Table* Database::getTable(const std::string& name) {
    auto it = tables.find(name);
    if (it != tables.end()) {
        return &it->second;
    }

    return nullptr;
}

void Database::save(const std::string& filename) {
    std::ofstream outfile{};
    outfile.open(filename, std::ios::out | std::ios::trunc);

    size_t tableCount = tables.size();
    outfile << tableCount << std::endl;
    for (const auto& [name, table] : tables) {
        outfile << name << std::endl;
        table.save(outfile);
    }
    outfile.close();
}

void Database::load(const std::string& filename) {
    std::ifstream input_file(filename);
    if (!input_file.is_open()) {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return;
    }

    std::string line{};
    size_t tableCount{};
    if (getline(input_file, line)) {
        tableCount = std::stoi(line);
    }

    tables.clear();
    for (size_t i = 0; i < tableCount; ++i) {
        std::string name{};
        getline(input_file, name);

        Table table(name);
        table.load(input_file);
        tables[name] = table;
    }

    input_file.close();
}
