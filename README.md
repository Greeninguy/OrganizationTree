# OrganizationTree
This is a Data Structures programming project that creates a tree data structure themed as an employee database.
A linked list is implemented for this tree data structure.

The main project cpp file contains a test harness which illustrates the functions of the Orgtree.  The test harness "WriteTest" files are included in the project directory.  

Input files must be formatted with the employee entrees formated as "Title, Name".  Input files must have employees listed by line in an "Pre-order" tree traversal ordering.  A line containing only a ')' indicates the end of a tree branch.

addRoot(title, name) adds a root node to the Orgtree.  The employee of the Orgtree is considered to be the highest ranking employee.  If the Orgtree already has a root, then a new root is created with the old root becoming it's child.

hire(Supervisor, title, name) adds a node to the OrgTree.  Supervisor parameter is reference to parent tree node
