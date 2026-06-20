#pragma once
#include <string>
#include <map>

enum class ProductType {
	WheatSeed = 1,
	CornSeed,
	Chicken,
	Cow,
	Wheat,
	Corn,
	Egg,
	Milk
};

struct ProductInfo {
	int id;
	std::string name;
	int buyPrice;
	int requiredCycles;
	ProductType gives;
	int quantity;
};

