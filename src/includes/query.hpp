// query.hpp
#ifndef QUERY_HPP
#define QUERY_HPP

#include "database.hpp"
#include <string>
#include <unordered_map>

class Query
{
public:
    Query() = default;
    Query(Database* db);
    Query(std::unordered_map<std::string, Database>* dbs, std::string* currentDb);
    ~Query() = default;

    void getQ();
    void excQ();

private:
    std::string userInput{};
    Database* dbptr{nullptr};
    std::unordered_map<std::string, Database>* databases{};
    std::string* currentDatabase{nullptr};
};

#endif // QUERY_HPP
