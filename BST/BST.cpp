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

void BST::deleteNode(node* node)
{
	//TODO: THIS ISN'T ALLOWED, MAKE SURE TO REDO
	if (node->leftChild != nullptr)
	{
		deleteNode(node->leftChild);
	}

	if (node->rightChild != nullptr)
	{
		deleteNode(node->rightChild);
	}

	delete node;
}

void BST::insert(const string word)
{
	// SEE IF THIS IS NECESSARY OR IF WE CAN USE == LATER TO DO A PROPER ATTACHMENT
	BST::node* node = findNode(word);

	if (node == nullptr)
	{
		BST::node* p = root;
		BST::node* q = nullptr;

		while (p != nullptr)
		{
			q = p;

			if (word < p->word)
			{
				p = p->leftChild;
			}
			else
			{
				p = p->rightChild;
			}
		}

		BST::node* newNode = new BST::node();

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
	else
	{
		node->count++;

		printNode(node);
	}
}

void BST::remove(const string word)
{
	BST::node* node = findNode(word);

	if (node == nullptr)
	{
		cout << word << " -1" << endl;

		return;
	}

	if (node->count == 1)
	{
		string word = node->word;

		deleteNode(node);

		cout << word << " 0";
	}
	else
	{
		node->count--;

		printNode(node);
	}
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

	if (p == nullptr)
	{
		cout << endl;
	}
	else
	{
		printNode(p->parent);
	}
}

void BST::child(const string word)
{
	BST::node* p = findNode(word);

	if (p == nullptr)
	{
		cout << endl;
	}
	else
	{
		cout << p->leftChild->word << ", " << p->rightChild->word << endl;
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
	}

	cout << "(" << ++index << ") " << node->word << " " << node->count << ", "; 

	if (node->rightChild != nullptr)
	{
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
	if (root == nullptr)
	{
		cout << endl;

		return;
	}

	node* x = root;

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
	if (root == nullptr)
	{
		cout << endl;

		return;
	}

	node* x = root;

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