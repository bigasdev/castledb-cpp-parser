#include <iostream>
#include <fstream>
#include "src/castledb_converter.hpp"

bool working = true;
bool converted = false;

std::vector<CastleData> data_db;

int main() {
    std::cout << "Hello, World!" << "\n";

    CastleDBConverter converter("res/helloworld.json");

    data_db = converter.extract_data("HelloWorld", {"Name", "X", "Y", "Char"});

    while(working){
        if(!converted){
            for (auto& m_data : data_db) {
                std::cout << "Data Name: " << m_data.name << "\n";

                for(size_t i = 0; i < std::stoi(m_data.data["Y"]); i++){
                        
                    for(size_t j = 0; j < std::stoi(m_data.data["X"]); j++){
                        std::cout << m_data.data["Char"];
                    }

                    std::cout << "\n";
                }

                std::cout << "\n";
            }
            converted = true;
        }

        if(converter.update("res/helloworld.json")){
            system("cls");

            data_db = converter.extract_data("HelloWorld", {"Name", "X", "Y", "Char"});
            converted = false;
        }
    }

    return 0;
}