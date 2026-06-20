#include "MarketManager.h"
#include "Market.h"
#include "ProductType.h"



 MarketManager::MarketManager(std::string name, std::string pass) : User(name, pass) {}

void MarketManager::openMarketCatalog() const
{
    Market::getInstance().openCatalog();
}

void MarketManager::restock(int id, int q)
{
    if (Market::getInstance().restock(id, q)) {
        std::cout << "Restocked successfully!\n";
    }
    else {
        std::cout << "Failed to restock: Invalid product ID or quantity!\n";
    }
}

void MarketManager::changePrice(int id, int p)
{
    if (Market::getInstance().changePrice(id, p)) {
        std::cout << "Price changed successfully!\n";
    }
    else {
        std::cout << "Failed to change price: Invalid product ID or price!\n";
    }
}

std::string MarketManager::getType() const
{
    return "MarketManager";
}

void MarketManager::profileInfo() const
{
    User::profileInfo();
    std::cout << "Type: MarketManager\n";
}

void MarketManager::logout()
{
    std::cout << "MarketManager logged out.\n";
}
