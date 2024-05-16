#include "castledb_converter.hpp"

CastleDBConverter::CastleDBConverter(const std::string filename)
{
    std::ifstream f(filename);
    data = json::parse(f);

    m_last_edited = std::to_string(std::filesystem::last_write_time(filename).time_since_epoch().count());
}

CastleDBConverter::~CastleDBConverter()
{

}

const std::vector<CastleData> CastleDBConverter::extract_data(const std::string sheetName, std::vector<std::string> keys)
{
    std::vector<CastleData> result;

    for(auto& sheet : data["sheets"]){
        if(sheet["name"] == sheetName){
            for(auto& line : sheet["lines"]){
                CastleData castleData;
                castleData.name = line["Name"];

                for(auto& key : keys){
                    if(line[key].is_number()){
                        castleData.data[key] = std::to_string(line[key].get<int>());
                        continue;
                    }
                    if(line[key].is_boolean()){
                        castleData.data[key] = std::to_string(line[key].get<bool>());
                        continue;
                    }

                    castleData.data[key] = line[key];
                }

                result.push_back(castleData);
            }
        }
    }

    return result;
}

bool CastleDBConverter::update(const std::string filename)
{
    if(m_last_edited != std::to_string(std::filesystem::last_write_time(filename).time_since_epoch().count())){
        std::ifstream f(filename);
        data = json::parse(f);

        m_last_edited = std::to_string(std::filesystem::last_write_time(filename).time_since_epoch().count());
        return true;
    }
    return false;
}
