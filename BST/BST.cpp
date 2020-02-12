#include "BST.h"

BST::BST()
{
	root = NULL;
}

BST::~BST()
{
	if (root != NULL)
	{
		deleteNode(root);
	}
}

void BST::deleteNode(node* node)
{
	//TODO: THIS SHIT ISN'T ALLOWED
	if (node->leftChild != NULL)
	{
		deleteNode(node->leftChild);
	}

	if (node->rightChild != NULL)
	{
		deleteNode(node->rightChild);
	}

	delete node;
}

void BST::insert(const string word)
{
	// SEE IF THIS IS NECESSAR OR IF WE CAN USE == LATER TO DO A PROPER ATTACHMENT
	BST::node* node = findNode(word);

	if (node == NULL)
	{
		BST::node* p = root;
		BST::node* q = NULL;

		while (p != NULL)
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
		newNode->leftChild = NULL;
		newNode->rightChild = NULL;
		newNode->parent = q;

		if (q == NULL)
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

	if (node == NULL)
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

	if (p == NULL)
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

	while (p != NULL)
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

	return NULL;
}

void BST::parent(const string word)
{
	node* p = findNode(word);

	if (p == NULL)
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

	if (p == NULL)
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
	if (root == NULL)
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
	if (node->leftChild != NULL)
	{
		list(index, node->leftChild);
	}

	cout << "(" << ++index << ") " << node->word << " " << node->count << ", "; 

	if (node->rightChild != NULL)
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
	if (p == NULL)
	{
		cout << endl;

		return;
	}

	while (p->leftChild != NULL)
	{
		p = p->leftChild;
	}

	if (p != NULL)
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
	if (p == NULL)
	{
		cout << endl;

		return;
	}

	while (p->rightChild != NULL)
	{
		p = p->rightChild;
	}

	if (p != NULL)
	{
		cout << p->word << endl;
	}
}

void BST::prev(const string word)
{
	if (root == NULL)
	{
		cout << endl;

		return;
	}

	node* x = root;

	if (x->leftChild != NULL)
	{
		max(x->leftChild);

		return;
	}

	node* y = x->parent;

	while (y != NULL && x == y->leftChild)
	{
		x = y;
		y = y->parent;
	}

	if (y != NULL)
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
	if (root == NULL)
	{
		cout << endl;

		return;
	}

	node* x = root;

	if (x->rightChild != NULL)
	{
		min(x->rightChild);

		return;
	}

	node* y = x->parent;

	while (y != NULL && x == y->rightChild)
	{
		x = y;
		y = y->parent;
	}

	if (y != NULL)
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