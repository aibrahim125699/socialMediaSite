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
};
