#pragma once

#include <iostream>
#include<string>

using namespace std;

class BST
{
public:
	BST();
	~BST();

	void insert(const string word);	// adds a word to the binary search tree
	void remove(const string word);	// decrements the count of a word in the binary search tree, or deletes it from the tree if it has a count of 1
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
		string word; // The word of the node
		int count = 1; // The amount of times the word has been inserted into the binary search tree
		node* leftChild = nullptr; // A pointer to the left child of the node
		node* rightChild = nullptr; // A pointer to the right child of the node
		node* parent = nullptr; // A pointer to the parent of the node
	};

	node* root = nullptr; // A pointer to the root of the binary search tree. If this is nullptr, no nodes exist in the tree.

	node* nextNode(node* p); // Returns a pointer to the successor node of p

	node* findNode(const string word); // Returns a pointer to the node with the given word

	node* minNode(node* p);

	void traverseDestruct(node* p);

	void min(node* p);

	void max(node* p);

	void list(int& index, node* p);

	void printNode(node* p);

	void deleteNode(node* p);

	bool isLeaf(node* p);

	bool isRoot(node* p) { return p == root; }

	int getChildCount(node* p);

	bool isLeftChild(node* p);

	bool isRightChild(node* p);
};