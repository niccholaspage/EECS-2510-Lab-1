//==============================================================================================
// File: BST.cpp - Binary search tree implementation
// c.f.: BST.h
//
// This class implements a binary search tree, filled with nodes as declared in BST.h.  
// Each node contains a word, the number of times the word has appeared, and pointers to 
// the left and right child of the node.
//
// Author:     Nicholas Nassar, University of Toledo
// Class:      EECS 2510-001 Non-Linear Data Structures, Spring 2020
// Instructor: Dr.Thomas
// Date:       Feb 23, 2020
// Copyright:  Copyright 2020 by Nicholas Nassar. All rights reserved.

#include "BST.h"

BST::BST()
{
	// constructor -- there's nothing to do other then making sure
	// the root pointer is a nullptr. The default value is in the
	// header, but I am doing it again for redundancy and clarity.
	//
	root = nullptr; // When a new binary search tree is constructed, there is no root node.
}

BST::~BST()
{
	// On deconstruction, we have to delete the entire tree by
	// deleting each node in the tree, one by one.
	//
	if (root == nullptr) // Check if the root node is null
	{
		return; // Return because there are no nodes to delete!
	}


	// Destroying the tree is done by doing a traversal through all
	// of the nodes and their children.
	traverseDestruct(root);

	// After the traverseDestruct method, we will have deleted
	// all of the nodes. By setting root to nullptr, we make sure
	// we don't have an old reference to the now non-existent root
	// node.
	root = nullptr;
}

void BST::traverseDestruct(node* p) {
	// This recursive method can be called on a given node to delete
	// its children and itself. Doing this recursively ensures that
	// every node will get deleted as long as this method is initially
	// called on the root node.
	//
	if (p->leftChild != nullptr) // Check if the left child of the node is not null
	{
		traverseDestruct(p->leftChild); // Since the node does have a left child, we will call the traverseDestruct method on the node
	}

	if (p->rightChild != nullptr) // Check if the right child is not null
	{
		traverseDestruct(p->rightChild); // Since the node does have a right child, we will call the traverseDestruct method on the node
	}

	// Now that we have properly deleted the children of the given node,
	// we are safe to delete the node since we have already taken care of
	// its children.
	//
	delete p;
}

void BST::deleteNode(node* p)
{
	// This method deletes the given node from the tree.
	// Depending on the amount of children of the node,
	// we must use different methods to delete the node
	// and properly adjust the tree.
	//
	int amountOfChildren = getChildCount(p); // Set the variable to the amount of children for the given node so we can handle each delete case

	if (amountOfChildren == 0) // If the node has no children,
	{
		if (isRoot(p))		   // lets check if the node is the root,
		{
			delete p;		   // if so, we can just delete the node,

			root = nullptr;	   // and set the root to nullptr, making the tree empty.
		}
		else				   // otherwise,
		{
			node* parent = p->parent; // get the parent of the node

			if (isLeftChild(p)) // check if the node is a left child
			{
				delete p; // Delete the node

				parent->leftChild = nullptr; // Set the parent's left child to null, as the node was deleted.
			}
			else if (isRightChild(p)) // otherwise, check if the node is a right child
			{
				delete p; // Delete the node

				parent->rightChild = nullptr; // Set the parent's right child to null, as the node was deleted.
			}
			else {
				// it should not be possible to get here, as the node
				// has to be a left or right child of its parent since
				// it has to have a parent.
				cout << "Internal error in deleteNode\n"; // Print out that something awful has happened.

				exit(1); // Exit the program - oops!
			}
		}

		return; // By the end of this case, we have deleted the node, so we can just return here.
	}

	if (amountOfChildren == 1)      // If the node has one child,
	{
		node* child = p->leftChild; // lets get the left child of the node,

		if (child == nullptr)      // If the child is null,
		{
			child = p->rightChild; // then the one child has to be the right child.
		}

		if (isRoot(p))    // If the given node is null,
		{
			root = child; // Set the tree's root to the child.

			child->parent = nullptr; // Since the child node is now the root, we set its parent to null

			delete p; // Delete the node, as it now has been removed from the tree
		}
		else              // Since the node is not the root, we have a bit more complicated of a process
		{
			node* parent = p->parent; // get the parent of the node

			if (isLeftChild(p)) // if the node is a left child of its parent,
			{
				parent->leftChild = child; // Since we are deleting node p, we must fix the parent's left child by making it p's child

				child->parent = parent; // Now, we update the parent of the child node to point to the parent

				delete p; // Delete the node, as it has now been removed from the tree
			}
			else if (isRightChild(p)) // if the node is a right child of its parent,
			{
				parent->rightChild = child; // Since we are deleting node p, we must fix the parent's right child by making it p's child

				child->parent = parent; // Now, we update the parent of the child node to point to the parent

				delete p; // Delete the node, as it has now been removed from the tree
			}
			else
			{
				// It should not be possible to get here, as node p should have been
				// either a left child or right child since it is not the root node.
				cout << "Internal error in deleteNode\n"; // Print out that something awful has happened during deletion.

				exit(1); // Exit the program - oops!
			}
		}

		return; // By the end of this case, we have deleted the node, so we can just return.
	}

	// We will only get to this point if node p has two children, as the other cases have already been taken care of
	node* y = nextNode(p); // Get the successor of node p

	// Perform "copy" of y's contents into p.
	p->word = y->word; // We set p's word to y's word
	p->count = y->count; // We set p's count to y's count

	if (y == p->rightChild) // If y (p's successor) is p's right child,
	{
		p->rightChild = y->rightChild; // Set p's right child to y's right child

		if (y->rightChild != nullptr)    // If y has a right child,
		{
			y->rightChild->parent = p;   // we need to fix its parent by setting it to node p.
		}
	}
	else // In this case, y is further down the tree since it is not p's direct right child.
	{
		p->rightChild->leftChild = y->rightChild;  // Set p's right child's left child to y's right child

		if (y->rightChild != nullptr)			   // If y's right child was not null,
		{
			y->rightChild->parent = p->rightChild; // We need to fix its parent by setting it to p's right child.
		}
	}

	delete y; // Now we delete node y, as it's contents have been copied into p.
}

void BST::insert(const string word)
{
	// To a add a word to the tree, we need to traverse through the nodes of the tree,
	// looking for the word. If we find it, we increment the node's counter and exit;
	// otherwise, we continue traversing through the node's children, going through the
	// left child if the word is less than the node's word that we are traversing, or
	// the right child if the word is greater than the node's word we are traversing.
	// If it is not found, we just make a new node and attach it to the tree.
	//
	node* p = root; // traverses the tree, starting at the root node
	node* q = nullptr; // lags one step behind p; used to update q's child to a new node if it was made.

	while (p != nullptr) // as long as there are more nodes:
	{
		q = p; // Set our lagging pointer to q

		if (word < p->word) // Check if the word we are inserting is less than p's word
		{
			p = p->leftChild; // If so, p gets set to old p's left child, so that we can check it.
		}
		else if (word > p->word) // Otherwise, check if our word is greater than p's word.
		{
			p = p->rightChild; // If so, p gets set to old p's right child, so that we can check it.
		}
		else // Since the word was not less than or greater than p's word, there is only one case remaining - it equals p's word
		{
			p->count++; // Since a node with the word already exists, we just increment the node's count by one.

			printNode(p); // We call this helper method to print out the word and count of node p

			return; // Since we don't need to insert any new nodes into the tree, we can just stop here. We are done!
		}
	}

	// Since we've gotten here, we weren't able to find a node
	// with the word already in the tree, so lets build a new
	// node to store the word.
	//
	node* newNode = new node(); // Construct a new node

	newNode->word = word; // Set the new node's word to the word we are inserting
	newNode->count = 1; // Redundantly set the count in the new node to 1
	newNode->leftChild = nullptr; // Since new nodes are added as leaves, left and right child pointers are null
	newNode->rightChild = nullptr;
	newNode->parent = q; // As q lags behind p in the end, the new node's parent is set to q.

	if (q == nullptr) // If q is nullptr, that means that the new node has no parent, so it is the root!
	{
		root = newNode; // Since the new node must be the root, we set the root of the tree to the new node.
	}
	else if (newNode->word < q->word) // Since the new node is not the root, we check if its word is less than its parent's.
	{
		q->leftChild = newNode; // If so, we set q's left child to the new node.
	}
	else // Otherwise, the new node's word must be greater than q,
	{
		q->rightChild = newNode; // so we set q's right child to the new node.
	}

	printNode(newNode); // Finally, we print the new node's word and count
}

void BST::remove(const string word)
{
	// This method removes the given word from a tree.
	// If we find a node with the word in the tree, we check
	// if its count is greater than one, and if so, decrement
	// the count by one. Otherwise, we delete the node from the
	// tree. If we can't find a node with the word, then we just
	// print out the word and -1 to indicate the node wasn't found.
	node* p = findNode(word); // Get a pointer to the node containing the word we are going to get rid of

	if (p == nullptr) // If we didn't find a node with the word in it,
	{
		cout << word << " -1" << endl; // We just print out the word and -1 to indicate the node wasn't found

		return; // Now we return because we are done, there is nothing to do anymore.
	}

	if (p->count > 1) // Since the node's count is greater than one,
	{
		p->count--;   // we just decrement the count by one.

		printNode(p); // We now print the node's word and count

		return; // Since we've taken care of decrementing the count, we are done!
	}

	// Since the node's count was 1, we call the deleteNode
	// method to remove the node from the tree properly.
	//
	deleteNode(p);

	// Since the node has been deleted from the tree now,
	// we print the word and 0 next to it, to show that
	// the word is no longer in the tree.
	//
	cout << word << " 0" << endl;
}

void BST::search(const string word)
{
	// This method searches the tree for the given word. If it is found,
	// we print the word and its count. Otherwise, we print out the word and
	// 0, to show it is not in the tree.
	//
	node* p = findNode(word); // Get a pointer to the node containing the word we are searching for

	if (p == nullptr) // If there is no node with the given word in the tree,
	{

		cout << word << " 0" << endl; // we just print the word and 0, showing the tree does not contain the node inside of it.
	}
	else // Otherwise,
	{
		printNode(p); // we just print out the node's word and count.
	}
}

BST::node* BST::findNode(const string word)
{
	// This helper method takes the given word and attempts to find a node
	// containing it. It either returns a pointer to the node if it is found,
	// or nullptr if nothing was found.
	//
	node* p = root; // We start at the root of the tree.

	while (p != nullptr) // While p is not null,
	{
		if (p->word == word) // We check if p's word is the word we are looking for,
		{
			return p;		// If it is, we return node p, as we have found it!
		}
		else if (word < p->word) // Otherwise, we check if the word is less than p's word.
		{
			p = p->leftChild;	 // If so, lets set p to old p's left child.
		}
		else
		{
			// Since p's word was not less than or equal to the given word,
			// it must be greater than the given word,
			p = p->rightChild; // so we set p to p's right child.
		}
	}

	return nullptr; // Since we were not able to find a node with the given word, we just return nullptr
}

void BST::parent(const string word)
{
	// This method prints the parent node of a node with the given word.
	// If a node with the given word isn't found, it just prints a
	// newline. It also prints a newline of the node does not have
	// a parent.
	//
	node* p = findNode(word); // Get a pointer to the node containing the given word

	if (p == nullptr || p->parent == nullptr) // If no node was found, or the node found does not have a parent,
	{
		cout << endl; // we just print a newline.
	}
	else // otherwise, we found the node and it has a parent,
	{
		cout << p->parent->word << endl; // so we print out the node's parent word.
	}
}

void BST::child(const string word)
{
	// This method prints the children nodes of a node with the given word.
	// If no node with the given word is found, a newline is printed. Otherwise,
	// the node's left and right child are printed, with a comma separating them.
	// If the node doesn't have a left or right child, NULL is printed in its
	// place.
	//
	node* p = findNode(word); // Get a pointer to the node containing the given word

	if (p == nullptr) // If p is nullptr, then we were not able to find a node with the given word,
	{
		cout << endl; // so we just print a newline.
	}
	else // otherwise,
	{
		// we get the left child word, or NULL if there is no left child
		string leftChildWord = p->leftChild == nullptr ? "NULL" : p->leftChild->word;

		// we also get the right child word, or NULL if there is no right child
		string rightChildWord = p->rightChild == nullptr ? "NULL" : p->rightChild->word;

		cout << leftChildWord << ", " << rightChildWord << endl; // We now print the left and right child words with a comma separated between them
	}
}

void BST::list()
{
	// This method traverses through the entire tree and prints out the nodes in a nicely formatted list
	// with indexes and the node's word and count.
	//
	if (root == nullptr) // If the root is nullptr, than there is nothing in the tree,
	{
		cout << "Set is empty" << endl; // so we just print out "Set is empty"
	}
	else // otherwise, we actually have nodes in the tree,
	{
		cout << "Set contains: "; // so we print out "Set contains: " as a prefix,

		int index = 0; // We set up a index variable to 0 that is incremented before printing a node

		list(index, root); // We now start our recursive traversal through the root node with our overloaded list method.

		cout << endl; // We finish off the output by printing out a newline, as we never did it inside the above method call.
	}
};

void BST::list(int& index, node* p)
{
	// This method does a recursive traversal through all of the nodes in the tree
	// and prints out their word and count with an index parameter. The index
	// parameter is passed by reference so that no matter which recursive call
	// of this method we are in, the correct index will always be printed out.
	// Through talking with Dr. Thomas, I learned that the index variable could
	// have been a class variable instead. I enjoy this method because it does
	// not require any cleanup or setup of a class variable.
	//
	if (p->leftChild != nullptr)   // If the left child of the node is not null,
	{
		list(index, p->leftChild); // we print out the left child node as well, recursively taking care of its children.

		// Since we have now printed out the left child node, we need to print
		// out a comma to separate it from the node we are about to print.
		//
		cout << ", ";
	}

	// We now print out the index AFTER incrementing it, as well as the node's
	// word and count.
	cout << "(" << ++index << ") " << p->word << " " << p->count;

	if (p->rightChild != nullptr) // If the right child of the node is not null,
	{
		// we print out a comma to separate the node we already printed from
		// the right child we are about to print.
		cout << ", ";

		list(index, p->rightChild); // we now print out the right child node as well, recursively taking care of its children.
	}
}

void BST::min()
{
	// This method prints out the minimum word in the tree, or a new line
	// if there are no nodes in the tree. Really, it just calls an overloaded
	// min method with the root node as the parameter.
	//
	min(root);
}

void BST::min(node* p)
{
	// This method prints out the word from the minimum node of the subtree
	// of the given node. If there is no minimum node, it just prints out a
	// newline.
	//
	node* min = minNode(p); // Gets the minimum node of the subtree of the given node

	if (min != nullptr) // If the minimum node is not null,
	{
		cout << min->word << endl; // print out its word.
	}
	else // Otherwise,
	{
		cout << endl; // we just print out a newline.
	}
}

BST::node* BST::minNode(node* p)
{
	// This method returns a pointer to a node that is the minimum node of a subtree
	// of the given node. If there is no minimum node, it just returns nullptr.
	//
	if (p == nullptr)   // If the given node is nullptr,
	{
		return nullptr; // there is no minimum node to return, so return nullptr!
	}

	while (p->leftChild != nullptr) // While we still have a left child of p,
	{
		p = p->leftChild; // we set p to old p's left child.
	}

	return p; // We now have the minimum node of the subtree, so we return a pointer to it.
}

void BST::max()
{
	// This method prints out the maximum word in the tree, or a new line
	// if there are no nodes in the tree. Really, it just calls an overloaded
	// max method with the root node as the parameter.
	//
	max(root);
}

void BST::max(node* p)
{
	// This method prints out the word from the maximum node of the subtree
	// of the given node. If there is no maximum node, it just prints out a
	// newline.
	//
	if (p == nullptr) // If the given node is nullptr,
	{
		cout << endl; // then we just print out a newline, as we don't have a max!

		return; // We return because we have nothing else to do.
	}

	while (p->rightChild != nullptr) // While we still have a right child of p,
	{
		p = p->rightChild; // we set p to old p's right child.
	}

	// We print out node p's word. We know p is not null because we only got
	// here if p was not null in the beginning, and p is only set to
	// NOT NULL right childs of the previous node at p.
	//
	cout << p->word << endl;
}

void BST::prev(const string word)
{
	// This method prints out the previous node's word for a node containing the
	// given word. If no node has the given word, a newline is printed.
	//
	node* x = findNode(word); // Get a pointer to the node containing the word we are getting the predecessor of

	if (x == nullptr) // If no node was found,
	{
		cout << endl; // we just print out a newline.

		return;	// We have nothing else to do since we didn't find a node, so we just return.
	}

	if (x->leftChild != nullptr) // If the node's left child is not null,
	{
		// we know that the node's predecessor is just the max of its child node,
		// so we just call the max method which will print the word associated with
		// the predecessor node.
		//
		max(x->leftChild);

		return; // We have found and printed the predecessor, so we are done and just return.
	}

	node* y = x->parent; // We get the parent of node x

	while (y != nullptr && x == y->leftChild) // While node y isn't null and x is still y's left child,
	{
		x = y;		   // we set x to node y,
		y = y->parent; // and we update y to be old y's parent.
	}

	if (y != nullptr) // If node y is not null,
	{
		cout << y->word << endl; // we have the predecessor of node x, so we print out its word.
	}
	else // otherwise,
	{
		cout << endl; // we don't have a predecessor, so we just print out a newline.
	}
}

BST::node* BST::nextNode(node* p)
{
	// This method returns the next node of the given node.
	// If the given node is a null pointer, or the given node
	// does not have a successor, we just return nullptr.
	//
	if (p == nullptr)	// If p is a null pointer,
	{
		return nullptr; // we return nullptr.
	}

	if (p->rightChild != nullptr)		// If the given node has a right child,
	{
		return minNode(p->rightChild);  // then the next node is the minimum node of node p's right child.
	}

	node* q = p->parent; // We now get node p's parent.

	while (q != nullptr && p == q->rightChild) // While q is not null and node p is q's right child,
	{
		p = q;		   // we set p to q,
		q = q->parent; // and we set q to old q's parent.
	}

	return q; // We return node q, which is the successor of node p, or null if no successor was found.
}

void BST::next(const string word)
{
	// This method prints out the next node's word for a node containing the
	// given word. If no node has the given word, a newline is printed.
	//
	node* x = findNode(word); // Get a pointer to the node containing the word we are getting the successor of

	node* next = nextNode(x); // Gets a pointer to the next node of the node x

	if (next != nullptr)			// If next is not nullptr, then we have a next node,
	{
		cout << next->word << endl; // so we print out next node's word!
	}
	else // otherwise,
	{
		cout << endl; // we just print out a newline.
	}
}

void BST::printNode(node* p)
{
	// This helper method prints the given node's word,
	// a space, and its count.
	// This assumes that the node passed in is not null!
	cout << p->word << " " << p->count << endl;
}

bool BST::isLeaf(node* p)
{
	// This helper method simply checks if the given node is a leaf,
	// meaning it has no left or right child.
	//
	return p->leftChild == nullptr && p->rightChild == nullptr;
}

bool BST::isRoot(node* p)
{
	// This helper method simply returns if the given node is the
	// root node of the tree.
	//
	return p == root;
}

int BST::getChildCount(node* p)
{
	// This helper method returns the amount of children a node has.
	// This method was taken from Dr. Thomas's lab PDF.
	//
	if (p == nullptr)
	{
		return -1; // can’t count children of no node!
	}

	if (isLeaf(p)) {
		return 0; // leaves have no child nodes
	}

	if (p->leftChild != nullptr && p->rightChild != nullptr) {
		return 2; // 2 children
	}

	if (p->leftChild != nullptr && p->rightChild == nullptr) {
		return 1; // 1 (left child)
	}

	if (p->leftChild == nullptr && p->rightChild != nullptr) {
		return 1; // 1 (right child)
	}

	// it should not be possible to get here
	cout << "Internal error in getChildCount\n"; // Defensive programming, something awful has happened!
	exit(1);                                     // We exit because we are not sure what to do at this point!
}

bool BST::isLeftChild(node* p)
{
	// This helper method simply checks if a node is its parent's left child.
	// This assumes that the node has a parent!
	// This method was taken from Dr. Thomas's lab PDF.
	//
	return p == p->parent->leftChild;
}

bool BST::isRightChild(node* p)
{
	// This helper method simply checks if a node is its parent's left child.
	// This assumes that the node has a parent!
	// This method was taken from Dr. Thomas's lab PDF.
	//
	return p == p->parent->rightChild;
}