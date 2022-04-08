#pragma once
#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <list>
#include <filesystem>
#include "Module.h"
class ModuleLines : public Module {
    public:
        ModuleLines() {};
        bool Init() override;
        /*void print() {
            for (const auto& l : lore) for (auto& il : l.second) std::cout << "[" << l.first << "][" << il.first << "] = " << il.second << std::endl;
        }*/
    private:
        std::map<char, std::map<std::string, std::string>> lore;
};