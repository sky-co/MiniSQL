// table.cpp
#include "table.hpp"
#include "globals.hpp"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <unordered_map>
#include <variant>

Table::Table(const std::string& name)
    : columnsNT{}
    , columns{}
    , name{name} {}

void Table::insertRow(const std::vector<ColumnType>& values) {
    if (values.size() != columnsNT.size()) {
        std::cerr << "Column count mismatch. Expected " << columnsNT.size() << " values." << std::endl;
        return;
    }

    for (size_t i = 0; i < columnsNT.size(); ++i) {
        columns[columnsNT[i].first].push_back(values[i]);
    }
    std::cout << "Row inserted into " << name << "." << std::endl;
}

void Table::deleteRows(const std::string& whereColumn, const std::string& whereOperator, const ColumnType& whereValue) {
    const auto& whereColData = columns.at(whereColumn);
    for (size_t i = 0; i < whereColData.size(); ++i) {
        bool conditionMet = false;
        if (whereOperator == "=") {
            conditionMet = (whereColData[i] == whereValue);
        } else if (whereOperator == "<") {
            conditionMet = (whereColData[i] < whereValue);
        } else if (whereOperator == ">") {
            conditionMet = (whereColData[i] > whereValue);
        }

        if (conditionMet) {
            for (auto& [colName, colData] : columns) {
                colData.erase(colData.begin() + i);
            }
            --i; // Adjust index after deletion
        }
    }
    std::cout << "Rows deleted from " << name << " where " << whereColumn << " " << whereOperator << " " << whereValue << "." << std::endl;
}

void Table::queryTable() const {
    std::cout << "Table " << name << " contents:" << std::endl;
    std::cout << "-------------------------------- " << std::endl;
    for (size_t i = 0; i < columnsNT.size(); ++i) {
        std::cout << columnsNT[i].first;
        if (i != columnsNT.size() - 1) {
            std::cout << ", ";
        } else {
            std::cout << std::endl;
        }
    }

    for (size_t i = 0; i < columns.begin()->second.size(); ++i) {
        for (const auto& column : columnsNT) {
            const auto& colData = columns.at(column.first);
            std::visit([](auto&& arg) {
                if constexpr (std::is_same_v<std::decay_t<decltype(arg)>, std::string>) {
                    std::cout << "\"" << arg << "\", ";
                } else if constexpr (std::is_same_v<std::decay_t<decltype(arg)>, double>) {
                    std::cout << std::fixed << std::setprecision(2) << arg << " ";
                } else {
                    std::cout << arg << ", ";
                }
            },
                       colData[i]);
        }
        std::cout << std::endl;
    }
}

void Table::queryTable(const std::vector<std::string>& columns) const {
    std::cout << "Table " << name << " contents:" << std::endl;
    std::cout << "-------------------------------- " << std::endl;
    for (size_t i = 0; i < columns.size(); ++i) {
        std::cout << columns[i];
        if (i != columns.size() - 1) {
            std::cout << ", ";
        } else {
            std::cout << std::endl;
        }
    }

    size_t rowCount = this->columns.begin()->second.size();
    for (size_t i = 0; i < rowCount; ++i) {
        for (const auto& column : columns) {
            const auto& colData = this->columns.at(column);
            std::visit([](auto&& arg) {
                if constexpr (std::is_same_v<std::decay_t<decltype(arg)>, std::string>) {
                    std::cout << "\"" << arg << "\", ";
                } else if constexpr (std::is_same_v<std::decay_t<decltype(arg)>, double>) {
                    std::cout << std::fixed << std::setprecision(2) << arg << " ";
                } else {
                    std::cout << arg << ", ";
                }
            },
                       colData[i]);
        }
        std::cout << std::endl;
    }
}

void Table::queryTable(const std::vector<std::string>& columns, const std::string& whereColumn, const std::string& whereOperator, const ColumnType& whereValue) const {
    std::cout << "Table " << name << " contents:" << std::endl;
    std::cout << "-------------------------------- " << std::endl;
    for (size_t i = 0; i < columns.size(); ++i) {
        std::cout << columns[i];
        if (i != columns.size() - 1) {
            std::cout << ", ";
        } else {
            std::cout << std::endl;
        }
    }

    const auto& whereColData = this->columns.at(whereColumn);
    size_t rowCount = whereColData.size();
    for (size_t i = 0; i < rowCount; ++i) {
        bool conditionMet = false;
        if (whereOperator == "=") {
            conditionMet = (whereColData[i] == whereValue);
        } else if (whereOperator == "<") {
            conditionMet = (whereColData[i] < whereValue);
        } else if (whereOperator == ">") {
            conditionMet = (whereColData[i] > whereValue);
        }
        if (conditionMet) {
            for (const auto& column : columns) {
                const auto& colData = this->columns.at(column);
                std::visit([](auto&& arg) {
                    if constexpr (std::is_same_v<std::decay_t<decltype(arg)>, std::string>) {
                        std::cout << "\"" << arg << "\", ";
                    } else if constexpr (std::is_same_v<std::decay_t<decltype(arg)>, double>) {
                        std::cout << std::fixed << std::setprecision(2) << arg << " ";
                    } else {
                        std::cout << arg << ", ";
                    }
                },
                           colData[i]);
            }
            std::cout << std::endl;
        }
    }
}

void Table::save(std::ofstream& outfile) const {
    auto rowCount = columns.begin()->second.size();
    outfile << rowCount << std::endl;

    const auto columnCount = columnsNT.size();
    outfile << columnCount << std::endl;

    for (const auto& column : columnsNT) {
        outfile << column.first << std::endl;
        outfile << column.second << std::endl;
    }

    for (const auto& [colName, colData] : columns) {
        for (const auto& value : colData) {
            std::visit([&outfile](auto&& arg) {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, int>) {
                    char type = 'i';
                    outfile << type << std::endl;
                    outfile << arg << std::endl;
                } else if constexpr (std::is_same_v<T, double>) {
                    char type = 'd';
                    outfile << type << std::endl;
                    outfile << arg << std::endl;
                } else if constexpr (std::is_same_v<T, std::string>) {
                    char type = 's';
                    outfile << type << std::endl;
                    outfile << arg << std::endl;
                }
            },
                       value);
        }
    }
}

void Table::load(std::ifstream& file) {
    std::string line{};
    getline(file, line);
    size_t rowCount = std::stoi(line);

    getline(file, line);
    size_t columnCount = std::stoi(line);
    columnsNT.clear();
    columns.clear();
    for (size_t i = 0; i < columnCount; ++i) {
        std::string name{};
        getline(file, name);

        std::string type{};
        getline(file, type);

        columnsNT.push_back({name, type});
        columns[name] = std::vector<ColumnType>(rowCount);
    }

    for (auto& [colName, colData] : columns) {
        for (size_t i = 0; i < rowCount; ++i) {
            ColumnType value{};

            getline(file, line);
            char type = line[0];
            if (type == 'i') {
                getline(file, line);
                value = std::stoi(line);
            } else if (type == 'd') {
                getline(file, line);
                value = std::stof(line);
            } else if (type == 's') {
                getline(file, line);
                value = line;
            }
            colData[i] = value;
        }
    }
}

void Table::addColumn(const std::string& name, const std::string& type) {
    columnsNT.push_back({name, type});
    std::cout << "Column " << name << " of type " << type << " added to " << this->name << "." << std::endl;
}

void Table::updateRow(const std::string& columnName, const std::string& operation, const ColumnType& value) {
    for (size_t i = 0; i < columns[columnName].size(); ++i) {
        std::visit([&](auto&& arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, int>) {
                if (operation == "=") {
                    arg = std::get<int>(value);
                } else if (operation == "+") {
                    arg += std::get<int>(value);
                } else if (operation == "-") {
                    arg -= std::get<int>(value);
                }
            } else if constexpr (std::is_same_v<T, double>) {
                if (operation == "=") {
                    arg = std::get<double>(value);
                } else if (operation == "+") {
                    arg += std::get<double>(value);
                } else if (operation == "-") {
                    arg -= std::get<double>(value);
                }
            }
        },
                   columns[columnName][i]);
    }
}

void Table::updateColumn(const std::string& columnName, const std::string& operation, const ColumnType& value) {
    for (size_t i = 0; i < columns[columnName].size(); ++i) {
        std::visit([&](auto&& arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, int>) {
                if (operation == "=") {
                    arg = std::get<int>(value);
                } else if (operation == "+") {
                    arg += std::get<int>(value);
                } else if (operation == "-") {
                    arg -= std::get<int>(value);
                }
            } else if constexpr (std::is_same_v<T, double>) {
                if (operation == "=") {
                    arg = std::get<double>(value);
                } else if (operation == "+") {
                    arg += std::get<double>(value);
                } else if (operation == "-") {
                    arg -= std::get<double>(value);
                }
            }
        },
                   columns[columnName][i]);
    }
}

void Table::updateColumn(const std::string& columnName, const std::string& operation, const ColumnType& value, const std::string& whereColumn, const std::string& whereOperator, const ColumnType& whereValue) {
    const auto& whereColData = columns.at(whereColumn);
    for (size_t i = 0; i < whereColData.size(); ++i) {
        bool conditionMet = false;
        if (whereOperator == "=") {
            conditionMet = (whereColData[i] == whereValue);
        } else if (whereOperator == "<") {
            conditionMet = (whereColData[i] < whereValue);
        } else if (whereOperator == ">") {
            conditionMet = (whereColData[i] > whereValue);
        }

        if (conditionMet) {
            std::visit([&](auto&& arg) {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, int>) {
                    if (operation == "=") {
                        arg = std::get<int>(value);
                    } else if (operation == "+") {
                        arg += std::get<int>(value);
                    } else if (operation == "-") {
                        arg -= std::get<int>(value);
                    }
                } else if constexpr (std::is_same_v<T, double>) {
                    if (operation == "=") {
                        arg = std::get<double>(value);
                    } else if (operation == "+") {
                        arg += std::get<double>(value);
                    } else if (operation == "-") {
                        arg -= std::get<double>(value);
                    }
                }
            },
                       columns[columnName][i]);
        }
    }
}
