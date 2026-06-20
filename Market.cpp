#include "Market.h"

Market::Market() {
    catalog = {
        {1, {1, "Wheat Seed", 10, 3, ProductType::Wheat, 20}},
        {2, {2, "Corn Seed", 15, 4, ProductType::Corn, 20}},
        {3, {3, "Chicken", 25, 3, ProductType::Egg, 10}},
        {4, {4, "Cow", 50, 5, ProductType::Milk, 5}},
        {5, {5, "Wheat", 15, 0, ProductType::Wheat, 20}},
        {6, {6, "Corn", 20, 0, ProductType::Corn, 20}},
        {7, {7, "Egg", 30, 0, ProductType::Egg, 15}},
        {8, {8, "Milk", 60, 0, ProductType::Milk, 10}}
    };
}
Market& Market::getInstance()
{
    {
        static Market instance;
        return instance;
    }
}
void Market::openCatalog() const
{
    std::cout << "=== MARKET CATALOG ===\n";
    for (auto const& [id, info] : catalog) {
        std::cout << id << ". " << info.name << " | Qty: " << info.quantity << " | Price: " << info.buyPrice << "\n";
    }
}

bool Market::buyItem(int productId, int qty)
{
    if (catalog.find(productId) == catalog.end()) return false;
    if (catalog[productId].quantity < qty) return false;
    catalog[productId].quantity -= qty;
    return true;
}

void Market::sellItem(int productId, int qty)
{
    if (catalog.find(productId) != catalog.end()) {
        catalog[productId].quantity += qty;
    }
}

bool Market::restock(int productId, int qty)
{
    if (catalog.find(productId) == catalog.end() || qty < 0) return false;
    catalog[productId].quantity += qty;
    return true;
}

bool Market::changePrice(int productId, int newPrice)
{
    if (catalog.find(productId) == catalog.end() || newPrice < 0) return false;
    catalog[productId].buyPrice = newPrice;
    return true;
}

const std::map<int, ProductInfo>& Market::getCatalog() const
{
    return catalog;
}

void Market::setCatalog(const std::map<int, ProductInfo>& newCatalog)
{
    catalog = newCatalog;
}
