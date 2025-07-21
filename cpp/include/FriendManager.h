#ifndef FRIENDSHIP_MANAGER_H
#define FRIENDSHIP_MANAGER_H

#include "crow.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <utility>

class FriendManager {
private:
	const std::string friendships_db = "friendships.json";
	crow::json::wvalue load_friendships() {
		std::ifstream file(friendships_db);
		std::stringstream buffer;
        	buffer << file.rdbuf();
        	return crow::json::load(buffer.str());
	}

	void save_friendships(const crow::json::wvalue& friendships) {
		std::ofstream file(friendships_db);
		if (file) {
			file << friendships.dump();
			file.flush();
		}
	}

	int find_relationship_index(const std::string& user1, const std::string& user2, const crow::json::wvalue& friendships) {
		std::vector<std::string> pair = {user1, user2};
		std::sort(pair.begin(), pair.end());

		for (size_t i = 0; i < friendships.size(); ++i) {
			auto& rel = friendships[i];
			std::vector<std::string> saved_pair;
			auto& users = rel["users"];

			for (size_t j = 0; j < users.size(); ++j) {
				saved_pair.push_back(crow::json::load(users[j].dump()).s());
			}

			std::sort(saved_pair.begin(), saved_pair.end());

			if (saved_pair == pair) {
				return static_cast<int>(i);
			}
		}
		return -1; // not found
	}
public:
};

#endif
