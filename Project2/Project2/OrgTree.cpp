#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>

#include "OrgTree.h"

//The OrgTree class Tree structure that uses a linked list of children.
//The TreeNode class has an inner class for the linked list of children called ChildrenList
//If p represents the bytes associated with each data value, and n is the number of nodes in the OrgTree,
//the space complexity for OrgTree is 7pn
//every TreeNode stems from a ChildNode except for the root TreeNode and the OrgTree class has one data value for the Root pointer

/**
addRoot member function adds a root to an OrgTree.  If a root already exists, then that root becomes a child of this new root.
The asymptotic runtime for this function is Omega(8)
*/
void OrgTree::addRoot(string title, string name)
{
	if (root == NULL) {
		root = new TreeNode(title, name);
	}
	else {
		TREENODEPTR tmp;
		tmp = root;		
		root = new TreeNode(title, name);
		root->childList = new TreeNode::ChildNode();
		root->childList->child = tmp;
		root->childList->child->parentList = root->childList;
		root->childList->parent = root;
	}
}

/**
getRoot member function returns a TREENODEPTR to the root of OrgTree
The asymptotic runtime for this function is Theta(2)
*/
OrgTree::TREENODEPTR OrgTree::getRoot()
{
	if (root) {
		return root;
	}
	return TREENULLPTR;
	
}

/**
hire member function will add a TreeNode to the node pointed to by the TREENODEPTR argument.
The asymptotic runtime for this function is Omega(n)
*/
void OrgTree::hire(TREENODEPTR boss, string newTitle, string newName)
{
	//If the parent node has no children
	if (!boss->childList) {		
		boss->childList = new TreeNode::ChildNode();
		boss->childList->child = new TreeNode(newTitle, newName);
		boss->childList->parent = boss;
		boss->childList->child->parentList = boss->childList;
	}
	//If the parent node has children, then the new node will become the right-most sibling child.
	else {
		TreeNode::ChildNode *tmp = boss->childList;
		while (tmp->sibling) {
			tmp = tmp->sibling;
		}
		tmp->sibling = new TreeNode::ChildNode();
		tmp = tmp->sibling;
		tmp->child = new TreeNode(newTitle, newName);
		tmp->child->parentList = tmp;
		tmp->parent = boss;
	}
}

/**
leftMostChild member function returns a TREENODEPTR to a TreeNode's left-most child
The asymptotic runtime for this function is Theta(2)
*/
OrgTree::TREENODEPTR OrgTree::leftmostChild(TREENODEPTR node)
{
	if (node->childList)
		return node->childList->child;
	else
		return TREENULLPTR;
	
}

/**
rightSibling member function returns a TREENODEPTR to a TreeNode's right sibling
The asymptotic runtime for this function is Theta(2)
*/
OrgTree::TREENODEPTR OrgTree::rightSibling(TREENODEPTR node)
{
	if (node->parentList->sibling)
		return node->parentList->sibling->child;
	else
		return TREENULLPTR;
	
}

/**
Recursive helper function for getSize.  
The asymptotic runtime for this function is Omega(n)
*/
unsigned int OrgTree::sizeHelper(TreeNode::ChildNode * child, unsigned int n)
{
	unsigned int t = n;
	TreeNode::ChildNode *c = child;
	bool b;
	do {
		b = false;
		if (c->child->childList) 
			t += sizeHelper(c->child->childList, 0);
		
		if (c->sibling) {
			c = c->sibling;
			b = true;
		}
		t++;
	} while (b == true);
	return t;
}

/**
getSize member function returns the number of Tree nodes in an OrgTree
Uses the helper function sizeHelper
The asymptotic runtime for this function is Omega(n) since it uses sizeHelper
*/
unsigned int OrgTree::getSize()
{
	if (!root) {
		return 0;
	}
	unsigned int t = 1;
	TREENODEPTR p = root;
	if (p->childList) {
		t += sizeHelper(p->childList, 0);
	}
	return t;
}

/**
fire function deletes the Tree node that has a matching title string as the input argument
The asymptotic runtime for this function is Omega(n) as it uses the findHelper function
*/
bool OrgTree::fire(string formerTitle)
{
	TREENODEPTR rootptr = root;
	TREENODEPTR firee = findHelper(rootptr->childList, formerTitle);
	if (!firee)
		return false;
	TREENODEPTR parent = firee->parentList->parent;

	if (parent->childList == firee->parentList) {		//case for if firee is leftmost child
		if (firee->parentList->sibling) {				//subcase if firee has siblings
			parent->childList = parent->childList->sibling;
			if (firee->childList) {
				TreeNode::ChildNode *pnt = parent->childList;
				while (pnt->sibling) {
					pnt = pnt->sibling;
				}
				pnt->sibling = firee->childList;
			}
		}
		else {		//subcase if firee does not have siblings
			if (firee->childList)
				parent->childList = firee->childList;
			else
				parent->childList = NULL;
		}
	}
	else {		//case for if firee is not leftmost child
		TreeNode::ChildNode *pnt = parent->childList;
		if (firee->parentList->sibling) {		//subcase for if firee has siblings
			while (pnt->sibling != firee->parentList) {
				pnt = pnt->sibling;
			}
			pnt->sibling = firee->parentList->sibling;
			if (firee->childList)		
				while (pnt->sibling) {
					pnt = pnt->sibling;
				}
			pnt->sibling = firee->childList;
		}
		else {		//subcase for if firee does not have siblings
			while (pnt->sibling != firee->parentList) {
				pnt = pnt->sibling;
			}
			if (firee->childList)
				pnt->sibling = firee->childList;
			else
				pnt->sibling = TREENULLPTR;
		}
	}
	delete firee;
	return true;
}

/**
Recursive helper function used by printSubTree.  Recursively traverses the OrgTree.
The asymptotic runtime for this function is Omega(n)
*/
void OrgTree::printSubTreeHelper(TreeNode::ChildNode *c, int count)
{
	bool b = false;
	string indentation = "        ";
	do {
		b = false;
		for (int i = 0; i < count; i++) {
			cout << indentation;
		}
		cout << c->child->title << ": " << c->child->name << endl;
		if (c->child->childList) {
			count++;
			printSubTreeHelper(c->child->childList, count);
			count--;
		}
		if (c->sibling) {
			c = c->sibling;
			b = true;
		}
	} while (b == true);
}
/**
printSubTree member function prints out the OrgTree in a specific manner
Uses the printSubTreeHelper member function to recursively traverse the OrgTree
The asymptotic runtime for this function is Omega(n) since it uses the printSubTreeHelper member function
*/
void OrgTree::printSubTree(TREENODEPTR subTreeRoot)
{
	cout << subTreeRoot->title << ": " << subTreeRoot->name << endl;
	if (subTreeRoot->childList) {
		TreeNode::ChildNode *p = subTreeRoot->childList;
		OrgTree::printSubTreeHelper(p, 1);
	}
	
}

/**
Recursive helper function for the write member function
The asymptotic runtime for this function is Omega(n)
*/
void OrgTree::writeHelper(TreeNode::ChildNode *child, ofstream& outFile)
{
	TreeNode::ChildNode *c = child;
	bool b;
	do {
		b = false;
		outFile << c->child->title << ", " << c->child->name << endl;
		if (c->child->childList) 
			writeHelper(c->child->childList, outFile);
		outFile << ')' << endl;
		if (c->sibling) {
			c = c->sibling;
			b = true;
		}
	} while (b == true);
}

/**
write member function writes the OrgTree in a specific manner into a file inputed into the argument
Uses the writeHelper function
The asymptotic runtime for this function is Omega(n) since it uses the writeHelper member function
*/
void OrgTree::write(string fileName)
{
	ofstream outFile(fileName);
	if (!outFile.is_open())
		cout << "Unable to open file " << fileName << endl;
	else {
		TREENODEPTR p = getRoot();
		outFile << p->title << ", " <<  p->name << endl;
		TreeNode::ChildNode *c = p->childList;
		writeHelper(c, outFile);
		outFile << ')' << endl;
		outFile.close();
	}
}

/**
read member function reads an OrgTree from a file inputed into the argument
Will return a OrgTree if the file contains a properly formatted text version of the OrgTree
Will return an empty tree if otherwise
The asymptotic runtime for this function is Omega(n)
*/
bool OrgTree::read(string filename)
{
	if (root) {		//returns false if the tree already exists
		cout << "This is not a new or empty tree" << endl;
		return false;
	}
	ifstream input(filename);
	if (!input.is_open()) {
		cout << "Could not open file" << endl;
		return false;
	}
	else {		//formatting error if the file does not start with a Tree Node to make
		if (input.peek() == ')') {
			cout << "Formatting error1" << endl;
			return false;
		}
		string name;
		string title;
		getline(input, title, ',');
		getline(input, name, '\n');
		addRoot(title, name);
		TREENODEPTR p = getRoot();
		
		

		if (input.peek() == ')') {		//formatting error for if the file does not have a Tree Node following the root node
			cout << "Formatting error2" << endl;
			return false;
			delete p;
		}
		getline(input, title, ',');
		getline(input, name, '\n');
		hire(p, title, name);
		
		p = p->childList->child;
		TreeNode::ChildNode *c = p->childList;

		while (!input.eof()) {		//case for if an input line contains the ')' character
			if (input.peek() == ')') {
				input.ignore(255, '\n');
				if (p->parentList) 
					p = p->parentList->parent;
				else if (input.peek()) {
					return true;
				}
				else {
					cout << "Formatting error3" << endl;
					return false;
					OrgTree::~OrgTree();
				}
			}

				else {				//case for if the input line contains a string to create a node with
				getline(input, title, ',');
				getline(input, name, '\n');
				hire(p, title, name);
				c = p->childList;
				while (c->sibling) {
					c = c->sibling;
				}
				p = c->child;
			}
		}
		return true;
	}
}
/**
Recursive helper function which traverses the OrgTree for the find helper function
The asymptotic runtime for this function is Omega(n)
*/
OrgTree::TREENODEPTR OrgTree::findHelper(TreeNode::ChildNode *child, string string)
{
	TreeNode::ChildNode *c = child;
	bool b;
	do {
		b = false;
		if (c->child->title == string) 
			return c->child;					
		if (c->child->childList) {
			TREENODEPTR p = findHelper(c->child->childList, string);
			if (p)
				return p;
		}		
		if (c->sibling) {
			c = c->sibling;
			b = true;
		}
			
	} while (b == true);
	return TREENULLPTR;
}
/**
find member function returns a TREENODEPTR that matches the title string inputed into the argument
Returns a TREENULLPTR if a matching title is not found
Uses the findHelper member function to recursively traverse the tree
The asymptotic runtime for this function is Omega(n) since it uses the findHelper member function
*/
OrgTree::TREENODEPTR OrgTree::find(string title)
{
	if (!root)
		return TREENULLPTR;
	TREENODEPTR p = root;
	if (p->title == title)
		return p;
	if (p->childList) {
		TreeNode::ChildNode *c = p->childList;
		p = findHelper(c, title);
		return p;
	}
	return TREENULLPTR;
}

OrgTree::OrgTree()
{
	root = NULL;
}
/**
Recursive helper function for the OrgTree destructor member function
Recursively traverses the tree an deletes the nodes that dynamically take memmory
The asymptotic runtime for this function is Omega(n)
*/
void OrgTree::deconstructorHelper(TreeNode::ChildNode *c)
{
	TreeNode::ChildNode *s;
	bool b;
	do {
		b = false;
		if (c->child->childList) {
			deconstructorHelper(c->child->childList);
		}
		if (c->sibling) {
			s = c;
			c = c->sibling;
			delete s->child;
			delete s;	
			b = true;
		}
	} while (b == true);
	delete c->child;
	delete c;
}

/**
The destructor member function for OrgTree uses the deconstructorHelper helper function
The asymptotic runtime for this function is Omega(n) since it uses the deconstructorHelper function
*/

OrgTree::~OrgTree()
{
	if (getRoot()) {
		TREENODEPTR p = getRoot();
		if (p->childList) {
			TreeNode::ChildNode *c = p->childList;
			deconstructorHelper(c);
		}
		delete p;
	}
}

OrgTree::TreeNode::TreeNode()
{
	name = "void";
	title = "void";
	childList = NULL;
	parentList = NULL;

}

OrgTree::TreeNode::TreeNode(string newTitle, string newName)
{
	name = newName;
	title = newTitle;
	childList = NULL;
	parentList = NULL;
}

OrgTree::TreeNode::ChildNode::ChildNode()
{
	child = NULL;
	sibling = NULL;
	parent = NULL;
}
