//==============================================================================================
// Main.cpp - Binary Search Tree program
//
// This program implements a Binary Search Tree data type with dynamic set operators
// to allow for insertion and deletion of items in a Binary Search Tree. The Binary
// Search Tree can be searched and minimum, maximum, next, and previous values can
// be retrieved. Children and parents of nodes can also be found. This program takes
// commands that can manipulate the Binary Search Tree and print information about it.
//
// Author:    Nicholas Nassar, University of Toledo
// Date:      Feb 18, 2020
// Copyright: Copyright 2020 by Nicholas Nassar. All rights reserved.

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
		else if (command == "parent")
		{
			bst->parent(argument);
		}
		else if (command == "child")
		{
			bst->child(argument);
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