#ifndef USER_H
#define USER_H
#include <string>
#include <vector>
#include <unordered_map>
#include <deque>
#include "Post.h"
#include "Chatroom.h"
#include "Notification.h"
#include "AVLTree.h"

class User {
private:
	const std::string username;
	std::vector<char> password;
	std::string email;
	std::vector<Post> posts;
	AVLTree friends;
	std::unordered_map<int, Chatroom> chatrooms;
	std::deque<Notification> notifications;

public:
	User(std::string uname, std::vector<char> pass, std::string mail, std::vector<Post> postList, AVLTree friendList) : username(uname), password(pass), email(mail), posts(postList), friends(friendList) {}

};

#endif
