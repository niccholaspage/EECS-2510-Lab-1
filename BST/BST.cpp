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
	delete p;
}

void BST::deleteNode(node* p)
{
	int amountOfChildren = getChildCount(p);

	if (amountOfChildren == 0) {
		if (isRoot(p))
		{
			delete p;

			root = nullptr;
		}
		else
		{
			node* parent = p->parent;

			if (isLeftChild(p))
			{
				delete p;

				parent->leftChild = nullptr;
			}
			else if (isRightChild(p))
			{
				delete p;

				parent->rightChild = nullptr;
			}
			else {
				// it should not be possible to get here
				cout << "Internal error in deleteNode\n";

				exit(1);
			}
		}

		return;
	}

	if (amountOfChildren == 1)
	{
		node* child = p->leftChild;

		if (child == nullptr)
		{
			child = p->rightChild;
		}

		if (isRoot(p))
		{
			root = child;

			child->parent = nullptr;

			delete p;
		}
		else
		{
			node* parent = p->parent;

			if (isLeftChild(p))
			{
				parent->leftChild = child;

				child->parent = parent;

				delete p;
			}
			else if (isRightChild(p))
			{
				parent->rightChild = child;

				child->parent = parent;

				delete p;
			}
			else
			{
				cout << "ERROR in deleteNode";

				exit(1);
			}
		}

		return;
	}

	// Two children
	node* y = nextNode(p);

	// Perform "copy" of y's contents into p
	p->word = y->word;

	p->count = y->count;

	if (y == p->rightChild)
	{
		p->rightChild = y->rightChild;

		if (y->rightChild != nullptr)
		{
			y->rightChild->parent = p;
		}
	}
	else
	{
		p->rightChild->leftChild = y->rightChild;

		if (y->rightChild != nullptr)
		{
			y->rightChild->parent = p->rightChild;
		}
	}

	delete y;
}

void BST::insert(const string word)
{
	node* p = root;
	node* q = nullptr;

	while (p != nullptr)
	{
		q = p;

		if (word < p->word)
		{
			p = p->leftChild;
		}
		else if (word > p->word)
		{
			p = p->rightChild;
		}
		else
		{
			p->count++;

			printNode(p);

			return;
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