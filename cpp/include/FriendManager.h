#include <string>
#include "UserManager.h"
using namespace std;

class FriendManager {
public:
	static void sendRequest(string senderUsername, string receiverUsername) {
		User* sender = UserManager::getUser(senderUsername);
		User* receiver = UserManager::getUser(receiverUsername);

		if (!sender || receiver || sender == receiver) {
			return;
		}

		if (sender->friends.search(receiverUsername)) {
			return;
		}

		receiver->receivedRequests.insert(sender);
		sender->sentRequests.insert(receiver);
	}

	static void cancelRequest(string senderUsername, string receiverUsername) {
		User* sender = UserManager::getUser(senderUsername);
		User* receiver = UserManager::getUser(receiverUsername);

		if (!sender || !receiver || sender == receiver) {
			return;
		}

		if (!sender->sentRequests.count(receiver)) {
			return;
		}

		sender->sentRequests.erase(receiver);
		receiver->receivedRequests.erase(sender);

		return;
	}

	static void acceptReject(string receiverUsername, string senderUsername, bool accepted) {
		User* receiver = UserManager::getUser(receiverUsername);
		User* sender = UserManager::getUser(senderUsername);

		if (!receiver || !sender || sender == receiver) {
			return;
		}

		if (!receiver->receivedRequests.count(sender)) {
			return;
		}

		receiver->receivedRequests.erase(sender);
		sender->sentRequests.erase(receiver);

		if (accepted) {
			receiver->addFriend(sender);
			sender->addFriend(receiver);
		}
		return;
	}

	static vector<User*> findMutuals(string username1, string username2) {
		User* user1 = UserManager::getUser(username1);
		User* user2 = UserManager::getUser(username2);

		if (!user1 || !user2) {
			return {};
		}

		vector<string> friendsList = user1->friends.inorderTraversal();
		vector<User*> mutuals;

		for (size_t i = 0; i < friendsList.size(); ++i) {
			string currentFriendUsername = friendsList[i];
			bool found = user2->friends.search(currentFriendUsername) ? true : false;

			if (found) {
				User* currentFriend = UserManager::getUser(currentFriendUsername);
				mutuals.push_back(currentFriend);
			}
		}
		return mutuals;
	}
};
