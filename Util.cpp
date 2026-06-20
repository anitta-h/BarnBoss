#include "Util.h"
#include "Player.h"
#include "TaskManager.h"
#include "MarketManager.h"
#include <fstream>

std::vector<std::string> Util::splitCommand(const std::string& input)
{
    std::vector<std::string> tokens;
    std::stringstream ss(input);
    std::string token;
    while (ss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

void Util::saveWorld(const std::map<std::string, User*>& users)
{
    std::ofstream outFile("users.txt");
    if (!outFile) {
        return;
    }
    for (const auto& pair : users) {
        outFile << pair.second->getUsername() << " "
            << pair.second->getPassword() << " "
            << pair.second->getType() << "\n";
    }
    outFile.close();
    std::cout << "Game saved successfully.\nGoodbye!\n";
}

void Util::loadWorld(std::map<std::string, User*>& users)
{
    std::ifstream inFile("users.txt");
    if (!inFile) {
        return;
    }

    std::string username, password, role;
    while (inFile >> username >> password >> role) {
        User* newUser = nullptr;
        if (role == "Player") {
            newUser = new Player(username, password);
        }
        else if (role == "TaskManager") {
            newUser = new TaskManager(username, password);
        }
        else if (role == "MarketManager") {
            newUser = new MarketManager(username, password);
        }

        if (newUser) {
            users[username] = newUser;
        }
    }
    inFile.close();
}

void Util::printHeader()
{
    std::cout << "========================================\n";
    std::cout << "            BARN BOSS\n";
    std::cout << "========================================\n\n";
}
