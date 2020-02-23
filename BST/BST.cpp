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
		return; 
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

	node* newNode = new node();

	newNode->word = word;
	newNode->count = 1;
	newNode->leftChild = nullptr;
	newNode->rightChild = nullptr;
	newNode->parent = q;

	if (q == nullptr)
	{
		root = newNode;
	}
	else if (newNode->word < q->word)
	{
		q->leftChild = newNode;
	}
	else {
		q->rightChild = newNode;
	}

	printNode(newNode);
}

void BST::remove(const string word)
{
	node* p = findNode(word);

	if (p == nullptr)
	{
		cout << word << " -1" << endl;

		return;
	}

	if (p->count > 1)
	{
		p->count--;

		printNode(p);

		return;
	}

	deleteNode(p);

	cout << word << " 0" << endl;
}

void BST::search(const string word)
{
	node* p = findNode(word);

	if (p == nullptr)
	{

		cout << word << " 0" << endl;
	}
	else
	{
		printNode(p);
	}
}

BST::node* BST::findNode(const string word)
{
	node* p = root;

	while (p != nullptr)
	{
		if (p->word == word)
		{
			return p;
		}
		else if (word < p->word)
		{
			p = p->leftChild;
		}
		else if (word > p->word)
		{
			p = p->rightChild;
		}
	}

	return nullptr;
}

void BST::parent(const string word)
{
	node* p = findNode(word);

	if (p == nullptr || p->parent == nullptr)
	{
		cout << endl;
	}
	else
	{
		cout << p->parent->word << endl;
	}
}

void BST::child(const string word)
{
	node* p = findNode(word);

	if (p == nullptr)
	{
		cout << endl;
	}
	else
	{
		string leftChildWord = p->leftChild == nullptr ? "NULL" : p->leftChild->word;
		string rightChildWord = p->rightChild == nullptr ? "NULL" : p->rightChild->word;

		cout << leftChildWord << ", " << rightChildWord << endl;
	}
}

void BST::list()
{
	if (root == nullptr)
	{
		cout << "Set is empty" << endl;
	}
	else
	{
		cout << "Set contains: ";

		int index = 0;

		list(index, root);

		cout << endl;
	}
};

void BST::list(int& index, node* p)
{
	if (p->leftChild != nullptr)
	{
		list(index, p->leftChild);

		cout << ", ";
	}

	cout << "(" << ++index << ") " << p->word << " " << p->count;

	if (p->rightChild != nullptr)
	{
		cout << ", ";

		list(index, p->rightChild);
	}
}

void BST::min()
{
	min(root);
}

void BST::min(node* p)
{
	node* min = minNode(p);

	if (p != nullptr)
	{
		cout << p->word << endl;
	}
	else
	{
		cout << endl;
	}
}

BST::node* BST::minNode(node* p)
{
	if (p == nullptr)
	{
		return nullptr;
	}

	while (p->leftChild != nullptr)
	{
		p = p->leftChild;
	}

	return p;
}

void BST::max()
{
	max(root);
}

void BST::max(node* p)
{
	if (p == nullptr)
	{
		cout << endl;

		return;
	}

	while (p->rightChild != nullptr)
	{
		p = p->rightChild;
	}

	if (p != nullptr)
	{
		cout << p->word << endl;
	}
}

void BST::prev(const string word)
{
	node* x = findNode(word);

	if (x == nullptr)
	{
		cout << endl;

		return;
	}

	if (x->leftChild != nullptr)
	{
		max(x->leftChild);

		return;
	}

	node* y = x->parent;

	while (y != nullptr && x == y->leftChild)
	{
		x = y;
		y = y->parent;
	}

	if (y != nullptr)
	{
		cout << y->word << endl;
	}
	else
	{
		cout << endl;
	}
}

BST::node* BST::nextNode(node* p)
{
	if (p == nullptr)
	{
		return nullptr;
	}

	if (p->rightChild != nullptr)
	{
		return minNode(p->rightChild);
	}

	node* q = p->parent;

	while (q != nullptr && p == q->rightChild)
	{
		p = q;
		q = q->parent;
	}

	return q;
}

void BST::next(const string word)
{
	node* x = findNode(word);

	node* next = nextNode(x);

	if (next != nullptr)
	{
		cout << next->word << endl;
	}
	else
	{
		cout << endl;
	}
}

void BST::printNode(node* p)
{
	cout << p->word << " " << p->count << endl;
}

bool BST::isLeaf(node* p)
{
	return p->leftChild == nullptr && p->rightChild == nullptr;
}

bool BST::isRoot(node* p)
{
	return p == root;
}

int BST::getChildCount(node* p) {
	if (p == nullptr) return -1; // can’t count children of no node!
	if (isLeaf(p)) return 0; // leaves have no child nodes
	if (p->leftChild != nullptr && p->rightChild != nullptr) return 2; // 2 children
	if (p->leftChild != nullptr && p->rightChild == nullptr) return 1; // 1 (l child)
	if (p->leftChild == nullptr && p->rightChild != nullptr) return 1; // 1 (r child)
	// it should not be possible to get here
	cout << "Internal error in getChildCount\n"; // practice defensive
	exit(1);                                     // programming!
}

bool BST::isLeftChild(node* p) { return p == p->parent->leftChild; }

bool BST::isRightChild(node* p) { return p == p->parent->rightChild; }