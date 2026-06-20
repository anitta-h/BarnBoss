#pragma once
#include "User.h"

class MarketManager : public User {
public:
     MarketManager(std::string name, std::string pass);
    void openMarketCatalog() const;
    void restock(int id, int q);
    void changePrice(int id, int p);
    std::string getType() const override;
    void profileInfo() const override;
    void logout() override;
};
