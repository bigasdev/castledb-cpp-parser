#include "castledb_converter.hpp"

CastleDBConverter::CastleDBConverter(const std::string filename)
{
    std::ifstream f(filename);
    data = json::parse(f);

    update_data();

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
                    if(line[key].is_null())continue;

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

const CastleData CastleDBConverter::extract_data_from_name(const std::string sheetName, const std::string name, std::vector<std::string> keys)
{
    for(auto& sheet : data["sheets"]){
        if(sheet["name"] == sheetName){
            for(auto& line : sheet["lines"]){
                if(line["Name"] == name){
                    CastleData castleData;
                    castleData.name = line["Name"];

                    for(auto& key : keys){
                        if(line[key].is_null())continue;

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

                    return castleData;
                }
            }
        }
    }

    return CastleData();
}

bool CastleDBConverter::update(const std::string filename)
{
    if(m_last_edited != std::to_string(std::filesystem::last_write_time(filename).time_since_epoch().count())){
        std::ifstream f(filename);
        data = json::parse(f);

        update_data();

        m_last_edited = std::to_string(std::filesystem::last_write_time(filename).time_since_epoch().count());
        return true;
    }
    return false;
}

void CastleDBConverter::update_data()
{
    for(auto& sheet : data["sheets"]){
        for(auto& line : sheet["lines"]){
            CastleData castleData;
            castleData.name = line["Name"];

            for(auto& key : line.items()){
                if(key.value().is_null())continue;

                if(key.value().is_number()){
                    castleData.data[key.key()] = std::to_string(key.value().get<int>());
                    continue;
                }
                if(key.value().is_boolean()){
                    castleData.data[key.key()] = std::to_string(key.value().get<bool>());
                    continue;
                }

                castleData.data[key.key()] = key.value();
            }

            m_cache[castleData.name] = castleData;
        }
    }
    //debug std 
    for(auto& [name, data] : m_cache){
        std::cout << name << std::endl;
        for(auto& [key, value] : data.data){
             std::cout << key << " : " << value << std::endl;
        }
        std::cout << "-" << std::endl;
    }
}
