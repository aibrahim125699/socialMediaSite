#include <string>

struct Node {
	std::string username;
	Node* left;
	Node* right;
	int height;

	Node(std::string uname) : username(uname), left(nullptr), right(nullptr), height(1) {}
};
