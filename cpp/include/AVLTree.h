#include <string>
#include <iostream>
#include "Node.h"

class AVLTree {
private:
	Node* root;

	int height(Node* node) {
		return (node == nullptr) ? 0 : node -> height;
	}

	int balanceFactor(Node* node) {
		return (node == nullptr) ? 0 : height(node->left) - height(node->right);
	}

	Node* rotateRight(Node* y) {
		Node* x = y->left;
		Node* T2 = x->right;

		x->right = y;
		y->left = T2;

		y->height = 1 + std::max(height(y->left), height(y->right));
		x->height = 1 + std::max(height(x->left), height(x->right));

		return x;
	}

	Node* rotateLeft(Node* x) {
		Node* y = x->right;
		Node* T2 = y->left;

		y->left = x;
		x->right = T2;

		x->height = 1 + std::max(height(x->left), height(x->right));
		y->height = 1 + std::max(height(y->left), height(y->right));

		return y;
	}

	Node* insert(Node* node, std::string username) {
		if (node == nullptr) {
			return new Node(username);
		}

		if (username < node->username) {
			node->left = insert(node->left, username);
		} else if (username > node->username) {
			node->right = insert(node->right, username);
		} else {
			return node;
		}

		node->height = 1 + std::max(height(node->left), height(node->right));
		
		int balance = balanceFactor(node);

		//rotations
		if (balance > 1 && username < node->left->username) { // left left
			return rotateRight(node);
		}

		if (balance < -1 && username > node->right->username) { //right right
			return rotateLeft(node);
		}

		if (balance > 1 && username > node->left->username) { // left right 
			node->left = rotateLeft(node->left);
			return rotateRight(node);
		}

		if (balance < -1 && username < node->right->username) { // right left
			node->right = rotateRight(node->right);
			return rotateLeft(node);
		}

		return node;
	}

	Node* minimum(Node* node) {
		Node* current = node;
		while (current->left != nullptr) {
			current = current->left;
		}
		return current;
	}

	Node* deleteNode(Node* node, std::string username) {
		if (node == nullptr) {
			return node;
		}

		if (username < node->username) {
			node->left = deleteNode(node->left, username);
		}
		else if (username > node->username) {
			node->right = deleteNode(node->right, username);
		} 
		else {
			if ( node->left == nullptr || node->right == nullptr) {
				Node* temp = node->left ? node->left : node->right;

				if (temp == nullptr) {
					temp = node;
					node = nullptr;
				}
				else {
					*node = *temp;
					delete temp;
				}
			}
			else {
				Node* temp = minimum(node->right);
				node->username = temp->username;
				node->right = deleteNode(node->right, temp->username);
			}
		}
		if (node == nullptr) {
			return node;
		}

		node->height = 1+ std::max(height(node->left), height(node->right));

		int balance = balanceFactor(node);

		if (balance > 1 && balanceFactor(node->left) >= 0) {
			return rotateRight(node);
		}

		if (balance > 1 && balanceFactor(node->left) < 0) {
			node->left = rotateLeft(node->left);
			return rotateRight(node);
		}
		
		if (balance < -1 && balanceFactor(node->right) <= 0) {
			return rotateLeft(node);
		}

		if (balance < -1 && balanceFactor(node->right) > 0) {
			node->right = rotateRight(node->right);
			return rotateLeft(node);
		}

		return node;
	}

	void traverseInorder(Node* node) {
		if (node != nullptr) {
			traverseInorder(node->left);
			std::cout << node->username << " ";
			traverseInorder(node->right);
		}
	}

public:
	AVLTree() : root(nullptr) {};
	
	void insert(std::string username) {
		root = insert(root, username);
	}

	void remove(std::string username) {
		root = deleteNode(root, username);
	}

	bool search(std::string username) {
		Node* current = root;
		while (current != nullptr) {
			if (username == current->username) {
				return true;
			}
			else if (username < current->username) {
				current = current->left;
			}
			else {
				current = current->right;
			}
		}
		return false;
	}

	void printInorder() {
		traverseInorder(root);
		std::cout << std::endl;
	}
};
