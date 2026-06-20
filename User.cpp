#include "User.h"
#include <iostream>

int User::nextId = 1;

User::User(std::string name, std::string password)
: username(name), password(password) 
{
	id = nextId++;
}

std::string User::getUsername() const
{
	return username;
}

bool User::checkPassword(const std::string& password) const
{
	return this->password == password;
}

void User::changePassword(const std::string& oldPass, const std::string& newPass)
{
    if (password == oldPass && newPass.length() >= 3) {
        password = newPass;
        std::cout << "Password changed!\n";
    }
    else std::cout << "Error changing password!\n";
}

void User::profileInfo() const
{
    std::cout << "ID: " << id << "\nUsername: " << username << "\n";
}

void User::logout()
{
    std::cout << "User " << username << " logged out successfully.\n";
}

int User::getId() const
{
    return id;
}

std::string User::getPassword() const
{
    return password;
}
