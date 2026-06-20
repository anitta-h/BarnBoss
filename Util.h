#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include "User.h"

class Util {
public:
    static std::vector<std::string> splitCommand(const std::string& input);

    static void saveWorld(const std::map<std::string, User*>& users);

    static void loadWorld(std::map<std::string, User*>& users);

    static void printHeader();
};
