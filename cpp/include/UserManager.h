#pragma once

#include "crow.h"
#include <string>
#include <utility>
#include "User.h"
#include <unordered_map>
#include "AuthService.h"
using namespace std;

class UserManager {
private:
	static unordered_map<string, User*> users;

public:
	static bool userExists(string username) {
		if (users.count(username) > 0) {
			return true;
		} else {
			return false;
		}
	}

	static void registerUser(string& username, string& password) {
		string passwordHashed = AuthService::hashPassword(password);

		User* newUser = new User(username, passwordHashed);
		users.insert({username, newUser});
	}

	
	static User* getUser(string username) {
		return users[username];
	}
	// should perform hashing here instead of main.cpp
};


std::unordered_map<std::string, User*> UserManager::users;
