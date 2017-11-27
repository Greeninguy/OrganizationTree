// Project2.cpp : Defines the entry point for the console application.
//The OrgTree class Tree structure that uses a linked list of children.
//The TreeNode class has an inner class for the linked list of children called ChildrenList
//If p represents the bytes associated with each data value, and n is the number of nodes in the OrgTree,
//the space complexity for OrgTree is 7pn
//every TreeNode stems from a ChildNode except for the root TreeNode and the OrgTree class has one data value for the Root pointer


#include "stdafx.h"
#include <string>
#include <iostream>

#include "OrgTree.h"

using namespace std;

void memoryLeakTest();

int main()
{
	OrgTree O1, O2;
	O1.addRoot("S1", "Ted");
	O1.addRoot("new boss", "Fred");								//addRoot works

	OrgTree::TREENODEPTR rootpnt = O1.getRoot();				//getRoot works
	O1.hire(O1.getRoot(), "S2", "Jimbo");						//hire works with getRoot
	O1.hire(O1.getRoot(), "S3", "Lincoln");

	OrgTree::TREENODEPTR findTester = O1.find("S2");			//this test worked
	OrgTree::TREENODEPTR findTesterNull = O1.find("doople");	
	O1.hire(findTester, "W1", "Timmy");
	O1.hire(O1.find("S1"), "W2", "Clinton");
	O1.hire(O1.find("S1"), "W5", "somename");
	O1.hire(O1.find("W1"), "P1", "Savvy");						//these worked
	O1.hire(O1.find("S2"), "W3", "nombre");
	O1.hire(O1.find("S3"), "W4", "Sally");
	O1.hire(O1.find("P1"), "SL1", "taladar");
	
	OrgTree::TREENODEPTR leftChildTest = O1.leftmostChild(O1.find("P1"));
	OrgTree::TREENODEPTR rightSiblingTest = O1.rightSibling(O1.find("W1"));		//these worked

	int c = O1.getSize();		//get sized worked this time
	
	O1.printSubTree(O1.getRoot());
	bool testFireFalse = O1.fire("doople");
	bool testFireTrue1 = O1.fire("W3");
	bool testFireTrue2 = O1.fire("W2");				//fire tests worked
	bool testFireTrue3 = O1.fire("S3");
	c = O1.getSize();
	
	O1.printSubTree(O1.getRoot());			//print works
	O1.printSubTree(O1.find("S1"));
	O1.printSubTree(O1.find("S2"));

	O1.write("WriteTest.txt");			//write works

	O2.read("WriteTest.txt");			//read works
	O2.write("WriteTest2.txt");
	O2.printSubTree(O2.getRoot());

	for (int i = 0; i < 50000; i++) {
		memoryLeakTest();
	}

	system("PAUSE");
    return 0;
}

void memoryLeakTest() {
	OrgTree O3;
	O3.addRoot("title", "name");
	for (int i = 0; i < 5; i++) {
		O3.hire(O3.getRoot(), "title", "name");
	}
	OrgTree O4;
	O4.addRoot("title", "name");
	for (int i = 0; i < 5; i++) {
		O4.hire(O4.getRoot(), "title", "name");
	}
}

