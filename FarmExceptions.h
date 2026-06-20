#pragma once
#include "BarnBossException.h" 

class CroplandFullException : public BarnBossException
{
public:
    CroplandFullException();
};

class InsufficientBalanceException : public BarnBossException
{
public:
    InsufficientBalanceException();
};

class InsufficientStockException : public BarnBossException
{
public:
    explicit InsufficientStockException(const std::string& details);
};

class InvalidInputException : public BarnBossException
{
public:
    explicit InvalidInputException(const std::string& msg);
};