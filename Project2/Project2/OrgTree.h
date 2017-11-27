#pragma once

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>

#define TREENODEPTR TreeNode*
#define TREENULLPTR NULL

using namespace std;

//The OrgTree class Tree structure that uses a linked list of children.
//The TreeNode class has an inner class for the linked list of children called ChildrenList
//If p represents the bytes associated with each data value, and n is the number of nodes in the OrgTree,
//the space complexity for OrgTree is 7pn
//every TreeNode stems from a ChildNode except for the root TreeNode and the OrgTree class has one data value for the Root pointer

class OrgTree {

public:

	class TreeNode {

	public:

		TreeNode();
		TreeNode(string newTitle, string newName);

		class ChildNode {

		public:

			TREENODEPTR child;
			TREENODEPTR parent;
			ChildNode *sibling;

			ChildNode();
		};

		string name;
		string title;
		ChildNode *childList;
		ChildNode *parentList;
	};

	OrgTree();
	void deconstructorHelper(TreeNode::ChildNode *c);
	~OrgTree();
	void addRoot(string title, string name);
	TREENODEPTR getRoot();
	TREENODEPTR findHelper(TreeNode::ChildNode *child, string string);
	TREENODEPTR find(string title);
	void hire(TREENODEPTR boss, string newTitle, string newName);
	TREENODEPTR leftmostChild(TREENODEPTR node);
	TREENODEPTR rightSibling(TREENODEPTR node);
	unsigned int sizeHelper(TreeNode::ChildNode *child, unsigned int n);
	unsigned int getSize();
	bool fire(string formerTitle);
	void printSubTreeHelper(TreeNode::ChildNode *child, int count);
	void printSubTree(TREENODEPTR subTreeRoot);
	void writeHelper(TreeNode::ChildNode *child, ofstream& ofile);
	void write(string filename);
	bool read(string filename);

private:
	TREENODEPTR root;
};

