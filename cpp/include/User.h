#ifndef USER_H
#define USER_H
#include <string>
#include <vector>
#include <deque>
#include "Post.h"
#include "Notification.h"
#include "AVLTree.h"

class User {
	friend class UserManager;
private:
	const std::string username;
	std::string password;
	std::string email;
	std::vector<Post> posts;
	AVLTree friends;
	std::deque<Notification> notifications;

public:
	User(std::string uname, std::string pass) {}
};

#endif
