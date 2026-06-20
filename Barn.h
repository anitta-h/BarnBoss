#pragma once
#include <map>
#include "ProductType.h"

class Barn {
std::map<int, int> storage;

public:
Barn();

void addProduct(int id, int quantity);
bool removeProduct(int id, int quantity);
int getQuantity(int productId) const;
void showBarn() const;

const std::map<int, int>& getStorage() const;
void setQuantity(int id, int qty);
};


