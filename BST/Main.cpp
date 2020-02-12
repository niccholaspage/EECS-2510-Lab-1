#include <iostream>
#include "BST.h"

using namespace std;

int main()
{
	BST* bst = new BST();

	while (true)
	{
		string input;

		getline(cin, input);

		string command;

		string argument;

		char delimeter = ' ';

		int index = input.find(' ');

		if (index == string::npos)
		{
			command = input;

			argument = "";
		}
		else
		{
			command = input.substr(0, index);

			//TODO: ARGUMENT ONLY NEEDS TO BE SINGLE WORD SO UPDATE THIS PLEASE.
			argument = input.substr(index + 1, input.length());
		}

		for (unsigned int i = 0; i < command.length(); i++)
		{
			command[i] = tolower(command[i]);
		}

		if (command == "insert")
		{
			bst->insert(argument);
		}
		else if (command == "delete")
		{
			bst->remove(argument);
		}
		else if (command == "search")
		{
			bst->search(argument);
		}
		else if (command == "next")
		{
			bst->next(argument);
		}
		else if (command == "prev")
		{
			bst->prev(argument);
		}
		else if (command == "min")
		{
			bst->min();
		}
		else if (command == "max")
		{
			bst->max();
		}
		else if (command == "list")
		{
			bst->list();
		}
		else if (command == "quit")
		{
			break;
		}
	}

	delete bst;

	return 0;
}