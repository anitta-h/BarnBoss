#include "FarmExceptions.h"

CroplandFullException::CroplandFullException() : BarnBossException("Cannot plant: Cropland full or no seeds!") {}

InsufficientBalanceException::InsufficientBalanceException() : BarnBossException("Insufficient balance to complete the purchase!") {}

InsufficientStockException::InsufficientStockException(const std::string& details) : BarnBossException("Barn Error: " + details) {}

InvalidInputException::InvalidInputException(const std::string& msg) : BarnBossException(msg) {}
