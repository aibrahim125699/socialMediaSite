#ifndef USER_H
#define USER_H
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include "Post.h"
#include "Chatroom.h"
#include "Notification.h"

class User {
private:
	const std::string username;
	std::vector<char> password;
	std::string email;
	std::vector<Post> posts;
	std::unordered_set<User> friends;
	std::unordered_map<int, Chatroom> chatrooms;
	std::deque<Notification> notifications;

public:
};

#endif
