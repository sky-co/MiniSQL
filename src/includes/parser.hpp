// parser.hpp
#ifndef PARSER_HPP
#define PARSER_HPP

#include "database.hpp"
#include <string>
#include <unordered_map>

class Parser
{
public:
    void parse(const std::string& input, std::unordered_map<std::string, Database>& databases, std::string& currentDatabase);
};

#endif // PARSER_HPP
