#include "crow.h"
#include <sodium.h>
#include <string>
#include <utility>
#include "User.h"
#include <unordered_map>
using namespace std;

class UserManager {
private:
	static unordered_map<string, User*> users;

public:
	bool userExists(string username) {
		if (users.count(username) > 0) {
			return true;
		} else {
			return false;
		}
	}

	void registerUser(string& username, string& password) {
		users.emplace(piecewise_construct, forward_as_tuple(username), forward_as_tuple(username, password));
	}

	bool validUser(string username, string password) {

		string hashedPassword;
		if (userExists(username)) {
			hashedPassword = users[username]->getPassword();
		} else {
			return false;
		}

		if (crypto_pwhash_str_verify(hashedPassword.c_str(), password.c_str(), password.length()) == 0 ) {
			return true;
		}
		else {
			return false;
		}
	}
	
	static User* getUser(string username) {
		return users["username"];
	}
	// should perform hashing here instead of main.cpp
};
