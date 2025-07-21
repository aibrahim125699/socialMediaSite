#include "crow.h"
#include <fstream>
#include <sodium.h>
#include <string>
#include <utility>
#include "User.h"


class UserManager {
private:
	const std::string credentials_db = "credentials.json";
	crow::json::wvalue credentials_json=load_users(credentials_db);

public:
	crow::json::rvalue load_users(const std::string& filename) {
		std::ifstream file(filename);
		std::stringstream buffer;
		buffer << file.rdbuf();
		return crow::json::load(buffer.str());
	}

	bool checkExistence(std::string username) {
        	auto& users = credentials_json["users"];
		for (size_t i=0; i < users.size(); ++i) {
			std::string saved_username = crow::json::load(users[i]["username"].dump()).s();
			if (saved_username == username) {
				return true;
			}
		}
		return false;
	}

	User createUser(std::string username, std::string password) {
		User new_user = User(username, password);
		return new_user;
	}

	void saveUser(const crow::json::wvalue& users, const std::string& filename) {
		std::ofstream file(filename);
		if (file) {
			file << users.dump();
			file.flush();
			file.close();
		}
	}

	void registerUser(std::string username, std::string password) {
        	auto& users = credentials_json["users"];
		
		crow::json::wvalue new_user;
		new_user["username"] = username;
		new_user["password"] = password;

		users[users.size()] = std::move(new_user);
		std::cout << "credentials_json = " << credentials_json.dump() << "\n";
		saveUser(credentials_json, credentials_db);

		//also should generate other files for friends, notifications etc.
	}

	bool validUser(std::string username, std::string password) {
		auto& users = credentials_json["users"];

		std::string hashedPassword;

		for (size_t i=0; i < users.size(); ++i) {
			std::string current = crow::json::load(users[i]["username"].dump()).s();
			if (current == username) {
				hashedPassword = crow::json::load(users[i]["password"].dump()).s();
				break;
			}
		}

		if (crypto_pwhash_str_verify(hashedPassword.c_str(), password.c_str(), password.length()) == 0 ) {
			return true;
		}
		else {
			return false;
		}
	}

	// should perform hashing here instead of main.cpp
};
