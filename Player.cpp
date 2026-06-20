#include "Player.h"
#include <iostream>
#include "Market.h"

Player::Player(std::string name, std::string pass) : User(name, pass), balance(100), score(0) {}

void Player::profileInfo() const
{
	User::profileInfo();
	std::cout << "Type: Player\nBalance: " << balance << "\nScore: " << score << "\n";
}

void Player::checkBarn() const
{
	barn.showBarn();
}

void Player::checkFarm() const
{
	std::cout << "Cropland: " << farm.cropland.size() << "/" << farm.croplandCapacity << " slots used.\n";
	std::cout <<"Farmland: " << farm.farmland.size() << "/" << farm.farmlandCapacity << " slots used.\n";
}

void Player::checkBalance() const
{
	std::cout << "Current Balance: " << balance << "\n";
}

void Player::addReward(int b, int s)
{
	this->balance += b; 
		this->score += s; 
}

void Player::checkScore() const
{
	std::cout << "Current Score: " << score << "\n";
}

	bool Player::buyItem(int productId, int quantity)
	{
		auto catalog = Market::getInstance().getCatalog();
		if (catalog.find(productId) == catalog.end()) {
			std::cout << "Item not found!\n";
			return false; 
		}
		int cost = catalog[productId].buyPrice * quantity;
		if (balance >= cost && Market::getInstance().buyItem(productId, quantity)) {
			balance -= cost;
			barn.addProduct(productId, quantity);
			std::cout << "The purchase was successful!\n";
			farm.updateCycles();
			return true; 
		}
		else {
			std::cout << "Purchase failed!\n";
			return false;
		}
	}

	bool Player::sellItem(int productId, int quantity)
{
		auto catalog = Market::getInstance().getCatalog();
		if (catalog.find(productId) == catalog.end()) return false; 
		if (barn.removeProduct(productId, quantity)) {
			balance += catalog[productId].buyPrice * quantity;
			Market::getInstance().sellItem(productId, quantity);
			std::cout << "The sale was successful!\n";
			farm.updateCycles();
			return true; 
		}
		else {
			std::cout << "Not enough stock in Barn!\n";
			return false;
		}
	}

void Player::sowPlant(int seedId)
{
	auto catalog = Market::getInstance().getCatalog();
	if (seedId != 1 && seedId != 2) { std::cout << "Invalid seed ID!\n"; return; }

	if (farm.cropland.size() < farm.croplandCapacity && barn.removeProduct(seedId, 1)) {
		int givesProductInt = static_cast<int>(catalog[seedId].gives);

		farm.cropland.push_back(GrowingItem(seedId, catalog[seedId].requiredCycles, givesProductInt));

		std::cout << "Plants planted successfully!\n";
		farm.updateCycles();
	}
	else { std::cout << "Cannot plant: Cropland full or no seeds!\n"; }
}

void Player::addAnimal(int animalId)
{
	auto catalog = Market::getInstance().getCatalog();
	if (animalId != 3 && animalId != 4) { std::cout << "Invalid animal ID!\n"; return; }

	if (farm.farmland.size() < farm.farmlandCapacity && barn.removeProduct(animalId, 1)) {
		int givesProductInt = static_cast<int>(catalog[animalId].gives);

		farm.farmland.push_back(GrowingItem(animalId, catalog[animalId].requiredCycles, givesProductInt));

		std::cout << "Animals added successfully!\n";
		farm.updateCycles();
	}
	else { std::cout << "Cannot add animal: Farmland full or no animal in barn!\n"; }
}

void Player::harvest()
{
	bool harvestedAny = false;
	for (auto it = farm.cropland.begin(); it != farm.cropland.end();) {
		if (it->currentCycles >= it->requiredCycles) {
			barn.addProduct(it->givesProductId, 1);
			it = farm.cropland.erase(it);
			harvestedAny = true;
		}
		else { ++it; }
	}
	for (auto it = farm.farmland.begin(); it != farm.farmland.end();) {
		if (it->currentCycles >= it->requiredCycles) {
			barn.addProduct(it->givesProductId, 1);
			it = farm.farmland.erase(it);
			harvestedAny = true;
		}
		else { ++it; }
	}
	std::cout << "Harvest completed!\n";
	farm.updateCycles();
}

void Player::completeTask(int taskId)
{
	Task* t = TaskBoard::getInstance().getTaskById(taskId);
	if (!t) { std::cout << "Task not found!\n"; return; }
	int prodId = -1;
	auto catalog = Market::getInstance().getCatalog();
	for (auto const& [id, info] : catalog) {
		if (info.name == t->requiredProduct) { prodId = id; break; }
	}
	if (prodId != -1 && barn.removeProduct(prodId, t->requiredQuantity)) {
		balance += t->rewardBalance;
		score += t->rewardScore;
		TaskBoard::getInstance().removeTask(taskId);
		std::cout << "Task completed successfully!\n";
		farm.updateCycles();
	}
	else { std::cout << "Not enough products in barn to complete task!\n"; }

}


void Player::expandCropland()
{
	int cost = 50 * farm.croplandCapacity;
	int reqScore = farm.croplandCapacity * 10;
	if (balance >= cost && score >= reqScore) {
		balance -= cost;
		farm.croplandCapacity++;
		farm.updateCycles();
		std::cout << "Cropland expanded!\n";
	}
	else {
		std::cout << "Not enough balance or score for expansion!\n";
	}
}

void Player::expandFarmland()
{
	int cost = 50 * farm.farmlandCapacity;
	int reqScore = farm.farmlandCapacity * 10;
	if (balance >= cost && score >= reqScore) {
		balance -= cost;
		farm.farmlandCapacity++;
		farm.updateCycles();
		std::cout << "Farmland expanded!\n";
	}
	else {
		std::cout << "Not enough balance or score for expansion!\n";
	}
}

int Player::getScore() const
{
	return score;
}

int Player::getBalance() const
{
	return balance;
}

void Player::setStats(int bal, int scr, int cc, int fc)
{
	balance = bal; score = scr; farm.croplandCapacity = cc; farm.farmlandCapacity = fc;
}

Barn& Player::getBarn()
{
	return barn;
}

Farm& Player::getFarm()
{
	return farm;
}

std::string Player::getType() const
{
	return "Player";
}

