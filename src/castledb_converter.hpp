#pragma once

#include "json.hpp"
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <filesystem>

using json = nlohmann::json;

struct CastleData{
    std::string name;
    std::unordered_map<std::string, std::string> data;
};

class CastleDBConverter {
public:
    CastleDBConverter(const std::string filename);
    ~CastleDBConverter();

    const std::vector<CastleData> extract_data(const std::string sheetName, std::vector<std::string> keys);
    const CastleData extract_data_from_name(const std::string sheetName, const std::string name, std::vector<std::string> keys);
    bool update(const std::string filename);
private:
    void update_data();

    json data;
    std::string m_last_edited;

    std::unordered_map<std::string, CastleData> m_cache;
}; 