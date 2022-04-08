#include "ModuleLines.h"
bool ModuleLines::Init() {
    std::ifstream file;
    std::list<std::string> ids;
    std::string str, idDef;
    char id;
    char* next;
    for (const auto& entry : std::filesystem::directory_iterator("./Text")) {
        if (entry.is_regular_file() && !entry.path().extension().compare(".csv")) {
            file = std::ifstream(entry.path());
            ids.clear();
            next = NULL;
            str = idDef = "";
            std::getline(file, str);
            idDef = strtok_s(_strdup(str.c_str()), "\t;", &next);
            while (next != 0 && strlen(next) != 0) ids.push_back(strtok_s(NULL, "\t;", &next));
            while (std::getline(file, str)) {
                id = strtok_s(_strdup(str.c_str()), "\t;", &next)[0];
                for (const auto& idi : ids) lore[id][idi] = strtok_s(NULL, "\t;", &next);
            }
            file.close();
        }
    }
    return true;
}