//==============================================================================================
// File: BST.h - Binary search tree
//
// Author:     Nicholas Nassar, University of Toledo
// Class:      EECS 2510-001 Non-Linear Data Structures, Spring 2020
// Instructor: Dr.Thomas
// Date:       Feb 23, 2020
// Copyright:  Copyright 2020 by Nicholas Nassar. All rights reserved.

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

	node* minNode(node* p); // Returns a pointer with the minimum string in the subtree of the given node

	void traverseDestruct(node* p); // Traverses through the given node and deletes its children recursively as well asitself

	void min(node* p); // Prints the node with the minimum string in the subtree of the given node

	void max(node* p); // Prints the node with the maximum string in the subtree of the given node

	void list(int& index, node* p); // Traverses through the children of a node as well as the node and prints

	void printNode(node* p); // Prints the given node's string and count

	void deleteNode(node* p); // Deletes the given node from the tree

	bool isLeaf(node* p); // Checks if the given node is a leaf (has no children)

	bool isRoot(node* p); // Checks if the given node is the root of the tree

	int getChildCount(node* p); // Returns the number of children the given node has

	bool isLeftChild(node* p); // Checks if the given node is a left child of its parent

	bool isRightChild(node* p); // Checks if the given node is a right child of its parent
};