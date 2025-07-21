#ifndef USER_H
#define USER_H
#include <string>
#include <vector>
#include <deque>
#include "Post.h"
#include "Notification.h"
#include "AVLTree.h"
#include <set>
using namespace std;

class User {
private:
	string username;
	string password;
	vector<Post> posts;
	deque<Notification> notifications;

public:
	AVLTree friends;
	set<User*> sentRequests;
	set<User*> receivedRequests;
	
	User() = default;

	User(string uname, string pass) : username(uname), password(pass) {}

	// User(const User& other) : username(other.username), password(other.password), posts(other.posts), friends(other.friends), notifications(other.notifications), sentRequests(other.sentRequests), recievedRequests(other.recievedRequests) {}

	// ~User()
	
	string getPassword() {
		return password;
	}

	string getUsername() {
		return username;
	}

	void addFriend(User* newFriend) {
		friends.insert(newFriend->getUsername());
	}

	void deleteFriend(User* formerFriend) {
		friends.remove(formerFriend->getUsername());
	}
};

#endif
