#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "User.h"
#include "Player.h"
#include "TaskManager.h"
#include "ProductType.h"
#include "TaskBoard.h"
#include "MarketManager.h"
#include "BarnBossException.h"
#include "FarmExceptions.h"
#include "Util.h"

int main() {
    std::map<std::string, User*> users;
    User* currentUser = nullptr;

    Util::printHeader();
    Util::loadWorld(users);

    std::string line;

    while (true) {
        std::cout << "> " << std::flush;

        if (!std::getline(std::cin, line)) {
            break;
        }

        if (line.empty()) {
            continue;
        }

        std::vector<std::string> args = Util::splitCommand(line);
        std::string command = args[0];

        if (command == "exit") {
            Util::saveWorld(users);
            for (auto& pair : users) {
                delete pair.second;
            }
            return 0; 
        }

        if (command == "logout") {
            if (!currentUser) {
                std::cout << "You are not logged into any profile!\n";
                std::cout << "\n";
                continue;
            }
            currentUser->logout();
            currentUser = nullptr;
            std::cout << "\n";
            Util::printHeader();
            continue;
        }

        try {
            if (command == "register") {
                if (args.size() < 4) {
                    std::cout << "Usage: register <username> <password> <Player|MarketManager|TaskManager>\n";
                    std::cout << "\n";
                    continue;
                }
                std::string username = args[1];
                std::string password = args[2];
                std::string role = args[3];

                if (users.find(username) != users.end()) {
                    std::cout << "User already exists!\n";
                    std::cout << "\n";
                    continue;
                }

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
                    std::cout << "User registered successfully!\n";
                }
                else {
                    std::cout << "Unknown role!\n";
                }
            }
            else if (command == "login") {
                if (args.size() < 3) {
                    std::cout << "Usage: login <username> <password>\n";
                    std::cout << "\n";
                    continue;
                }
                std::string username = args[1];
                std::string password = args[2];

                auto it = users.find(username);
                if (it != users.end() && it->second->checkPassword(password)) {
                    currentUser = it->second;
                    std::cout << "Welcome, " << currentUser->getUsername() << "!\n";
                }
                else {
                    std::cout << "Invalid username or password!\n";
                }
            }
            else {
                if (!currentUser) {
                    std::cout << "Please log in first!\n";
                    std::cout << "\n";
                    continue;
                }

                Player* playerPtr = dynamic_cast<Player*>(currentUser);
                TaskManager* taskMgrPtr = dynamic_cast<TaskManager*>(currentUser);

                if (command == "profileInfo") {
                    currentUser->profileInfo();
                }
                else if (command == "checkBarn") {
                    if (playerPtr) playerPtr->checkBarn();
                    else std::cout << "Only players have a barn!\n";
                }
                else if (command == "checkBalance") {
                    if (playerPtr) playerPtr->checkBalance();
                    else std::cout << "Only players have a balance!\n";
                }
                else if (command == "openMarketCatalog") {
                    std::cout << "=== MARKET CATALOG ===\n";
                    std::cout << "1. Wheat Seed | Qty: 20 | Price: 10\n";
                    std::cout << "2. Corn Seed  | Qty: 20 | Price: 15\n";
                    std::cout << "3. Chicken    | Qty: 10 | Price: 25\n";
                    std::cout << "4. Cow        | Qty: 5  | Price: 50\n";
                    std::cout << "5. Wheat      | Qty: 20 | Price: 15\n";
                    std::cout << "6. Corn       | Qty: 20 | Price: 20\n";
                    std::cout << "7. Egg        | Qty: 15 | Price: 30\n";
                    std::cout << "8. Milk       | Qty: 10 | Price: 60\n";
                }
                else if (command == "buyItem") {
                    if (args.size() < 3) {
                        std::cout << "Usage: buyItem <productId> <quantity>\n";
                        std::cout << "\n";
                        continue;
                    }
                    if (playerPtr) playerPtr->buyItem(std::stoi(args[1]), std::stoi(args[2]));
                }
                else if (command == "sellItem") {
                    if (args.size() < 3) {
                        std::cout << "Usage: sellItem <productId> <quantity>\n";
                        std::cout << "\n";
                        continue;
                    }
                    if (playerPtr) playerPtr->sellItem(std::stoi(args[1]), std::stoi(args[2]));
                }
                else if (command == "sowPlant") {
                    if (args.size() < 2) {
                        std::cout << "Usage: sowPlant <seedId>\n";
                        std::cout << "\n";
                        continue;
                    }
                    if (playerPtr) playerPtr->sowPlant(std::stoi(args[1]));
                }
                else if (command == "addAnimal") {
                    if (args.size() < 2) {
                        std::cout << "Usage: addAnimal <animalId>\n";
                        std::cout << "\n";
                        continue;
                    }
                    if (playerPtr) playerPtr->addAnimal(std::stoi(args[1]));
                }
                else if (command == "harvest") {
                    if (playerPtr) playerPtr->harvest();
                }
                else if (command == "showTaskBoard" || (command == "showTasks" && taskMgrPtr)) {
                    std::cout << "=== TASK BOARD ===\n";
                    int idx = 1;
                    for (const auto& task : TaskBoard::getInstance().getTasks()) {
                        std::cout << idx++ << ". Deliver " << task.requiredQuantity << " "
                            << task.requiredProduct << " -> Reward: " << task.rewardBalance
                            << " Balance, " << task.rewardScore << " Score\n";
                    }
                }
                else if (command == "addTask" && taskMgrPtr) {
                    if (args.size() < 5) {
                        std::cout << "Usage: addTask <product> <qty> <rewardB> <rewardS>\n";
                        std::cout << "\n";
                        continue;
                    }
                    taskMgrPtr->addTask(args[1], std::stoi(args[2]), std::stoi(args[3]), std::stoi(args[4]));
                }
                else if (command == "showScoreboard") {
                    std::cout << "=== SCOREBOARD ===\n";
                    int idx = 1;
                    for (const auto& pair : users) {
                        Player* p = dynamic_cast<Player*>(pair.second);
                        if (p) {
                            std::cout << idx++ << ". " << p->getUsername()
                                << " | Score: 0 | Balance: " << p->getBalance() << "\n";
                        }
                    }
                }
                else {
                    std::cout << "Invalid or unknown command: " << command << "!\n";
                }
            }
        }
        catch (const BarnBossException& e) {
            std::cout << e.what() << "\n";
        }
        catch (const std::exception& e) {
            std::cout << "Invalid parameters provided for the command!\n";
        }

        std::cout << "\n";
    }

    for (auto& pair : users) {
        delete pair.second;
    }

    return 0;
}