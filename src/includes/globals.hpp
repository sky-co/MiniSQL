// globals.hpp
#ifndef GLOBALS_HPP
#define GLOBALS_HPP
#include <fstream>
#include <variant>

extern std::ifstream inputFile;

using ColumnType = std::variant<int, double, std::string>;

std::ostream& operator<<(std::ostream& os, const ColumnType& column);

#endif // GLOBALS_HPP
