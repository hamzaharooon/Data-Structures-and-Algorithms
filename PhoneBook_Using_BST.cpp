#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

ofstream outf;		//output fstream used for file handling

class data{		//class named data which stores all the user data
	long long int number;
	char fname[20], lname[20], email[40];
	data *left, *right;
	friend class tree;
};

class tree{
public:
	
	data* root;		//ptr name root of data class type
	tree(){			//constructor to dynamically give root the value of data
		root = new data();
		root = NULL;
	}

	void create()		//Function to input the data from user
	{
		int k = 0; 
		data *tmp, *p, *parent = NULL;
		tmp = root;
		p = new data();
		
		cout << "\nFirst Name: ";		//inputs first and last name
		cin >> p->fname;
		cout << "\nLast Name: ";
		cin >> p->lname;
		
		do{ 							//checks for any anomaly in ph number
			cout << "\nPhone number: ";
			cin >> p->number;
			k = numchck(p->number);
		} 
		while (k != 1);
		
		do{ 							//checks for any anomaly in ph number
			cout << "\nEmail-ID: ";
			cin >> p->email;
			k = mailchck(p->email);
		}
		while (k != 1);
		
		p->left = NULL;					// nulls the left & right keys of tree
		p->right = NULL;
		
		if (root == NULL){				//checks if root isnt NULL then it shows BST is empty 
			root = p;
		}
		
		else {
	// tmp is not NULL, so we need to find the correct place to insert the new node
	while (tmp != NULL)		
	{
		// Keep track of the current parent node
		parent = tmp;		
		
		// Compare the fname of the new node with the fname of the current node
		// If the new node's fname is less than the current node's fname, move to the left child
		if (strcmp(p->fname, tmp->fname) < 0)
			tmp = tmp->left;
		// Otherwise, move to the right child
		else
			tmp = tmp->right;
	}

	// Insert the new node as either the left or right child of the parent node,
	// depending on whether its fname is less than or greater than the parent's fname
	if (strcmp(p->fname, parent->fname) < 0)
		parent->left = p;
	else
		parent->right = p;
}

	}

// This function checks if a given number d has 11 digits
int numchck(long long int d){
	// Initialize a count c to keep track of the number of digits in d
	int c = 0;
	
	// Divide d by 11 repeatedly until it is less than or equal to 0
	// Each time we divide d by 10, we increment the count by 1
	while (d > 0)
	{
		c++;
		d /= 10;
	}

	// If the count is 10, return 1 to indicate that d has 10 digits
	if (c == 11) return 1;
	
	// Otherwise, print an error message and return 0
	cout << "Number Invalid";
	return 0;
}


// This function checks if a given email address (a) is valid
int mailchck(char a[]){
	// Initialize a counter (j) to keep track of the number of '@' symbols in a
	// Initialize a loop variable (i) to iterate through the characters in a
	int j = 0, i = 0;

	// Iterate through the characters in a
	while (a[i] != '\0')
	{
		// If a character is an '@' symbol, increment the counter
		if (a[i] == '@') j++;
		
		// Move to the next character
		i++;
	}

	// If the counter is 1, return 1 to indicate that a is a valid email address
	if (j == 1) return 1;
	
	// Otherwise, print an error message and return 0
	cout << "Email id Invalid";
	return 0;
}


// This function prints the nodes of a binary tree in inorder traversal order
void inorder()
{
	// Call the helper function inordertrav() to traverse the tree and print the nodes
	inordertrav(root);
}


// This function traverses a binary tree in inorder traversal order and prints the nodes
void inordertrav(data *t)
{
	// If the current node is not NULL, traverse the left subtree, print the node, and then traverse the right subtree
	if (t != NULL)
	{
		inordertrav(t->left);
		
		// Print the contact details for the current node
		cout << "\nContact Details:\n";
		cout << "\n\nFirst name: " << t->fname << "\tLast name: " << t->lname << "\nPhone Number: " << t->number << "\tEmail id: " << t->email;
		
		inordertrav(t->right);
	}
}


// This function returns the node with the minimum value in a binary search tree
data* minValueNode(struct data *l)
{
	// Set the current node to the root of the tree
	data *current = l;

	// Iterate down the left side of the tree to find the leftmost leaf
	while (current->left != NULL)
		current = current->left;

	// Return the leftmost leaf (which will have the minimum value in the tree)
	return current;
}

// This function deletes a node with a given first name (a) from a binary search tree
data* deleteNode(struct data *root, char a[20])
{
	// If the tree is empty, return NULL
	if (root == NULL) return root;

	// If the first name of the node to be deleted is less than the first name of the current node,
	// search for the node to be deleted in the left subtree
	if (strcmp(a, root->fname) < 0)
		root->left = deleteNode(root->left, a);

	// If the first name of the node to be deleted is greater than the first name of the current node,
	// search for the node to be deleted in the right subtree
	else if (strcmp(a, root->fname) > 0)
		root->right = deleteNode(root->right, a);

	// If the first name of the node to be deleted is equal to the first name of the current node,
	// delete the current node
	else
	{
		// If the current node has no left child, return its right child as the new root of the subtree
		if (root->left == NULL)
		{
			data *temp = root->right;
			return temp;
		}
		// If the current node has no right child, return its left child as the new root of the subtree
		else if (root->right == NULL)
		{
			data *temp = root->left;
			return temp;
		}

		// If the current node has both a left and a right child,
		// find the node with the minimum value in the right subtree and replace the current node with it
		data *temp = minValueNode(root->right);
		root->number = temp->number;
		strcpy(root->lname, temp->lname);
		strcpy(root->fname, temp->fname);
		strcpy(root->email, temp->email);
		root->right = deleteNode(root->right, temp->fname);
	}

	// Return the root of the modified subtree
	return root;
}


// This function allows the user to edit the data for a node with a given first name (a) in a binary search tree
data* edit(data *root, char a[])
{
	// If the tree is empty, return NULL
	if (root == NULL) return root;

	// If the first name of the node to be edited is less than the first name of the current node,
	// search for the node to be edited in the left subtree
	if (strcmp(a, root->fname) < 0)
		root->left = edit(root->left, a);

	// If the first name of the node to be edited is greater than the first name of the current node,
	// search for the node to be edited in the right subtree
	else if (strcmp(a, root->fname) > 0)
		root->right = edit(root->right, a);
	
	// If the first name of the node to be edited is equal to the first name of the current node,
	// allow the user to edit the data for the current node
	else
	{
		// Prompt the user to choose which data value to edit
		int x;
		cout << "Enter the data choice to edit:\n1.First name\t2.Last name\t3.Phone number\t4.Email id:\n";
		cin >> x;
		
		// Prompt the user to enter the new value for the chosen data field
		cout << "\nEnter the new value:";
		
		// Update the chosen data field with the new value
		switch (x)
		{
			case 1:
				cin >> root->fname;
				break;
			case 2:
				cin >> root->lname;
				break;
			case 3:
				cin >> root->number;
				break;
			case 4:
				cin >> root->email;
				break;
			default:
				cout << "Value not modifed";
		}
	}

	// Return the root of the modified tree
	return root;
}


	// This function searches for a node with a given first name (a) in a binary search tree and prints its data
void searc(data *root, char a[])
{
	// If the tree is not empty, search for the node with the given first name
	if (root)
	{
		// If the first name of the node to be searched for is less than the first name of the current node,
		// search for the node in the left subtree
		if (strcmp(a, root->fname) < 0)
			searc(root->left, a);

		// If the first name of the node to be searched for is greater than the first name of the current node,
		// search for the node in the right subtree
		else if (strcmp(a, root->fname) > 0)
			searc(root->right, a);

		// If the first name of the node to be searched for is equal to the first name of the current node,
		// print the data for the current node
		else
		{
			cout << "\nContact Details:\n";
			cout << "First name: " << root->fname << "\tLast name: " << root->lname << "\nPhone Number: " << root->number << "\tEmail id: " << root->email;
		}
	}
}

// This function writes the data for all the nodes in a binary tree to a file
void filee(data *t)
{
	// If the current node is not NULL, traverse the left subtree, write the data for the current node to the file, and traverse the right subtree
	if (t != NULL)
	{
		filee(t->left);
		outf << "\nContact Details:\n" << "First name: " << t->fname << "\tLast name: " << t->lname << "\nPhone Number: " << t->number << "\tEmail id: " << t->email;
		filee(t->right);
	}
}


};

int main()
{
	tree q;
	char c, a[20];
	int x;
	cout << "\n#Phone Book using BST\nEnter contacts for Phone book creation:\n";
	
	do {
		cout << "\nEnter the Contact Details:\n";
		q.create();
		cout << "\nContinue?";
		cin >> c;
	} 
	while (c == 'y');
	
	cout << "\nCreation Successful\n";
	
	do {
		cout << "Enter the choice :\n1.Insert\t2.Delete\t3.Edit\t4.Search\t5.Print Phone book ?\n";
		cin >> x;
		switch (x)
		{
			case 1:
				q.create();
				cout << "\nContact Insertion successful";
				break;
			case 2:
				cout << "\nEnter the First name:";
				cin >> a;
				q.root = q.deleteNode(q.root, a);
				cout << "\n1 Contact deleted successfully";
				break;
			case 3:
				cout << "\nEnter the First name:";
				cin >> a;
				q.root = q.edit(q.root, a);
				cout << "\nChanges updated";
				break;
			case 4:
				cout << "\nEnter the First name:";
				cin >> a;
				q.searc(q.root, a);
				break;
			case 5:
				q.inorder();
				break;
			default:
				cout << "\nOption Invalid";
		}

		outf.open("Contacts.txt", ios::trunc);
		q.filee(q.root);
		cout << "\nContinue?\n";
		cin >> c;
		system("cls");
	} while (c == 'y');
	
	outf.close();
	return 0;
}

/*
Data Set to Test

abcd
efgh
12345678901
abcd@xyz.com

dcba
haha
12345678903
xyz@abc.com

*/

