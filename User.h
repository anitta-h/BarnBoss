#pragma once
#include <string>

class User {
	protected:
	int id;
	std::string username;
	std::string password;
	static int nextId;

	public:
	User(std::string name, std::string password);
	virtual ~User() = default;

	std::string getUsername() const;
	int getId() const;
	std::string getPassword() const;

	bool checkPassword(const std::string& password) const;
	void changePassword(const std::string& oldPass, const std::string& newPass);
	virtual void profileInfo() const;
	virtual void logout();
	virtual std::string getType() const = 0;
	
};
