#include "Barn.h"
#include "ProductType.h"
#include <iostream>
#include "Market.h"

Barn::Barn()
{
	for (int i = 1; i <= 8; ++i) {
		storage[i] = 0;
	}
}

void Barn::addProduct(int id, int quantity)
{
storage[id] += quantity;
}

bool Barn::removeProduct(int id, int quantity)
{
	if (storage[id] >= quantity) {
		storage[id] -= quantity;
		return true;
	}
	return false;
}

int Barn::getQuantity(int productId) const
{
	return storage.at(productId);
}


void Barn::showBarn() const
{
	std::cout << "=== BARN ===\n";
	auto catalog = Market::getInstance().getCatalog();
	for (int i = 1; i <= 8; ++i) {
		std::cout << catalog.at(i).name << ": " << storage.at(i) << "\n";
	}
}

const std::map<int, int>& Barn::getStorage() const
{
	return storage;
}

void Barn::setQuantity(int id, int qty)
{
	storage[id] = qty;
}
