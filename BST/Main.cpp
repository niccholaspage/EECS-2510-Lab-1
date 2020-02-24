//==============================================================================================
// Main.cpp - Binary Search Tree program
//
// This program implements a Binary Search Tree data type with dynamic set operators
// to allow for insertion and deletion of items in a Binary Search Tree. The Binary
// Search Tree can be searched and minimum, maximum, next, and previous values can
// be retrieved. Children and parents of nodes can also be found. This program takes
// commands that can manipulate the Binary Search Tree and print information about it.
//
// Author:     Nicholas Nassar, University of Toledo
// Class:      EECS 2510-001 Non-Linear Data Structures, Spring 2020
// Instructor: Dr.Thomas
// Date:       Feb 23, 2020
// Copyright:  Copyright 2020 by Nicholas Nassar. All rights reserved.

#include <iostream>
#include "BST.h"

using namespace std;

bool doesCommandRequireArgument(string command)
{
	// This helper method just checks if the given command
	// requires an argument to function properly.
	//
	return command == "insert" || command == "delete" || command == "search" || command == "next" || command == "prev"
		|| command == "parent" || command == "child";
}

void printHelp()
{
	// This method prints out a small description of the program as well as the commands
	// available to the user as reference for using the program.
	//
	cout << "This program implements a Binary Search Tree data type with commands to manipulate and print out nodes of the tree.\n";
	cout << "Available Commands:\n";
	cout << "insert <string>\n";
	cout << "delete <string>\n";
	cout << "search <string>\n";
	cout << "min\n";
	cout << "max\n";
	cout << "next <string>\n";
	cout << "prev <string>\n";
	cout << "list\n";
	cout << "parent <string>\n";
	cout << "child <string>\n";
	cout << "help\n";
	cout << "quit\n";
}

int main()
{
	// This is the entry point of the application, so we construct the binary search
	// tree and start the command loop to accept commands from the user to manipulate
	// the tree.
	//
	BST* bst = new BST(); // We instantiate the tree we will work with

	while (true) // We loop forever, as we will be accepting commands for the lifetime of the program
	{
		string command; // Create a variable to store the command.

		cin >> command; // We pipe console input into the command.

		// Since commands are case insensitive, we loop through all of the
		// characters in the command,
		for (unsigned int i = 0; i < command.length(); i++)
		{
			command[i] = tolower(command[i]); // and we set each character to the lowercase version of itself.
		}


		// We now have a large if statement to dispatch commands without arguments
		// to our tree. If we wanted to do this in a different possibly cleaner way,
		// we could have a class for each command that implements a Command interface,
		// and register commands in a map type structure, with the key being the word
		// of the command, and the value being an instance of the class. Obviously,
		// that is very complex for a project like this, especially considering we
		// don't need to get into language features like that for this project.
		//
		if (command == "min")
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
		else if (command == "help")
		{
			printHelp();
		}
		else if (command == "quit")
		{
			// For the quit command, we are not just dispatching something to the tree.
			// Instead, we are using a break statement, which will actually break us out
			// of the while loop and continue execution of the remaning lines of code.
			break;
		}
		else if (doesCommandRequireArgument(command)) // If the command requires an argument,
		{
			string argument; // we create a variable for the argument,

			cin >> argument; // and we pipe console input into the argument.

			// We now have another large if statement to dispatch commands with arguments
			// to our tree.
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
		}
	}

	// At this point, we have broken out of the while loop
	// because the quit command has been given.
	//
	delete bst; // We delete the tree before ending the program

	return 0; // We return 0, as we have not experienced an error, and our program has exited!
}