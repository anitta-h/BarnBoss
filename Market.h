#pragma once
#include "ProductType.h"
#include <map>
#include <iostream>

class Market {
private:
    std::map<int, ProductInfo> catalog;
    Market();
    Market(const Market&) = delete;
    Market& operator=(const Market&) = delete;
public:
    static Market& getInstance();

    void openCatalog() const;
    bool buyItem(int productId, int qty);
    void sellItem(int productId, int qty);
    bool restock(int productId, int qty);
    bool changePrice(int productId, int newPrice);
    const std::map<int, ProductInfo>& getCatalog() const;
    void setCatalog(const std::map<int, ProductInfo>& newCatalog);
};
