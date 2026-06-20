#pragma once
#include <stdexcept>
#include <string>

class BarnBossException : public std::exception
{
private:
    std::string message;

public:
    BarnBossException() = default;
    explicit BarnBossException(const std::string& message);

    const char* what() const noexcept override;
};
