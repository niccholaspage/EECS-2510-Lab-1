#include "BST.h"

BST::BST()
{
	root = nullptr;
}

BST::~BST()
{
	if (root != nullptr)
	{
		deleteNode(root);
	}
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

	cout << "Unhandled case!";
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
	node* node = findNode(word);

	if (node == nullptr)
	{
		cout << word << " -1" << endl;

		return;
	}

	if (node->count > 1)
	{
		node->count--;

		printNode(node);

		return;
	}

	deleteNode(node);

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
	//TODO: Fix list formatting
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

void BST::list(int& index, node* node)
{
	if (node->leftChild != nullptr)
	{
		list(index, node->leftChild);

		cout << ", ";
	}

	cout << "(" << ++index << ") " << node->word << " " << node->count;

	if (node->rightChild != nullptr)
	{
		cout << ", ";

		list(index, node->rightChild);
	}
}

void BST::min()
{
	min(root);
}

void BST::min(node* p)
{
	if (p == nullptr)
	{
		cout << endl;

		return;
	}

	while (p->leftChild != nullptr)
	{
		p = p->leftChild;
	}

	if (p != nullptr)
	{
		cout << p->word << endl;
	}
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

void BST::next(const string word)
{
	node* x = findNode(word);

	if (x == nullptr)
	{
		cout << endl;

		return;
	}

	if (x->rightChild != nullptr)
	{
		min(x->rightChild);

		return;
	}

	node* y = x->parent;

	while (y != nullptr && x == y->rightChild)
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

void BST::printNode(node* node)
{
	cout << node->word << " " << node->count << endl;
}

bool BST::isLeaf(node* p)
{
	return p->leftChild == nullptr && p->rightChild == nullptr;
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