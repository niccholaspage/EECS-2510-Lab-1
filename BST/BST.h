#pragma once

#include <iostream>
#include<string>

using namespace std;

class BST
{
public:
	BST();
	~BST();

	void insert(const string word);	// adds word to binary search tree
	void remove(const string word);	// deletes word from binary search tree, MAGICALLY NAME THIS DELETE
	void search(const string word);	// searches the binary search tree for the word

	void min();	// Prints the minimum value of the set.
	void max();	// Prints the maximum value of the set.

	void next(const string word); // Prints the successor of the given word.
	void prev(const string word); //Prints the predecessor of the given word.

	void list(); // Prints a list of all words in the tree.

	void parent(const string word); // Prints the word contained in the parent of the node whose key is the given word.
	void child(const string word); // Prints the words contained in the left and right child nodes of the node containing the given word.
private:
	struct node
	{
		string word;
		int count = 1;
		node* leftChild = nullptr;
		node* rightChild = nullptr;
		node* parent = nullptr;
	};

	node* root = nullptr;

	node* nextNode(node* p);

	node* findNode(const string word);

	node* minNode(node* node);

	void min(node* node);

	void max(node* node);

	void list(int& index, node* node);

	void printNode(node* node);

	void deleteNode(node* node);

	bool isLeaf(node* p);

	bool isRoot(node* p) { return p == root; }

	int getChildCount(node* p);

	bool isLeftChild(node* p);

	bool isRightChild(node* p);
};