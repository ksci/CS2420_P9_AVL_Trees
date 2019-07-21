#include "Node.h"
#include <string>

class AVLTree {

public:
	AVLTree();
	~AVLTree();

	void Insert(int data);
	Node* Search(int data);
	void Remove(int data);
	void InOrderTraversal();
	void PreOrderTraversal();
	void Print();
	int Size();
	

	Node* root;

private:
	Node* InsertHelper(Node* cursor, int data);
	Node* SearchHelper(Node* cursor, int data);
	Node* RemoveHelper(Node* cursor, int data);
	void InOrderHelper(Node* cursor);
	void PreOrderHelper(Node* cursor);
	void PrintHelper(std::string& offset, Node* cursor);
	int SizeHelper(Node* cursor);
	void DestructorHelper(Node* cursor);
	Node* RebalanceTree(Node* grandparent, int relativeHeightGrandParent);
	int FindRelativeHeight(Node* cursor);

};