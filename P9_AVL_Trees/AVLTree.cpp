#include "AVLTree.h"
#include <iostream>
#include <string>

AVLTree::AVLTree() {
	root = nullptr;
}
AVLTree::~AVLTree() {
	if (root) {
		DestructorHelper(root);
	}
}
void AVLTree::DestructorHelper(Node* cursor) {
	if (!cursor) {
		return;
	}
	else if (cursor->IsLeaf()) {
		delete cursor;
		return;
	}
	DestructorHelper(cursor->left);
	DestructorHelper(cursor->right);
	delete cursor;
}

//Precondition: an integer value is passed in, the tree may be empty or partially filled
//Postcondition:  the integer will be placed in the correct position of the tree
//according to the standard for a binary search tree: every parent has a child
//less than or equal on the left and a child greater than on the right
void AVLTree::Insert(int value) {
	root = InsertHelper(root, value);
}
//The AVL tree has additional functionality to rebalance the tree if necessary so
//that no child branch is more than one longer than another
Node* AVLTree::InsertHelper(Node* cursor, int value) {
	
	//we've found the right place to put our value
	if (!cursor) {
		Node* newNode = new Node(value, nullptr, nullptr);
		return newNode;
	}

	//put the value on the left side of the tree
	else if (value <= cursor->value) {
		cursor->left = InsertHelper(cursor->left, value);
		cursor->UpdateHeight();
		int relativeHeight = FindRelativeHeight(cursor);
		if (relativeHeight > 1 || relativeHeight < -1) {
			cursor = RebalanceTree(cursor, relativeHeight);
		}
		return cursor;
	}

	//put the value on the right side of the tree
	else {
		cursor->right = InsertHelper(cursor->right, value);
		cursor->UpdateHeight();
		int relativeHeight = FindRelativeHeight(cursor);
		if (relativeHeight > 1 || relativeHeight < -1) {
			cursor = RebalanceTree(cursor, relativeHeight);
		}
		return cursor;
	}
	cursor->UpdateHeight();
}

Node* AVLTree::Search(int value) {
	return SearchHelper(root, value);
}
Node* AVLTree::SearchHelper(Node* cursor, int value) {
	
	if (!cursor) {
		return nullptr;
	}
	else if (cursor->value == value) {
		return cursor;
	}
	else if (value < cursor->value) {
		return SearchHelper(cursor->left, value);
	}
	else if (value > cursor->value) {
		return SearchHelper(cursor->right, value);
	}
	else {
		return nullptr;
	}
}

void AVLTree::Remove(int value) {
	root = RemoveHelper(root, value);
}
Node* AVLTree::RemoveHelper(Node* cursor, int value) {
	
	if (!cursor) {
		return cursor;
	}
	else if (cursor->value == value) {
		if (cursor->IsLeaf()) {
			delete cursor;
			return nullptr;
		}
		//two children
		else if ((cursor->left) && (cursor->right)) {
			Node* temp = cursor->right;
			//find the successor
			if (temp->left) {
				while (temp->left) {
					temp = temp->left;
				}
				//node to replace now found
			}
			cursor->value = temp->value;
			cursor->right = RemoveHelper(cursor->right, temp->value);
			return cursor;
		}
		//one child
		else {
			if (cursor->left) {
				Node* temp = cursor->left;
				delete cursor;
				return temp;
			}
			else {
				Node* temp = cursor->right;
				delete cursor;
				return temp;
			}
		}
	}
	else if (value < cursor->value) {
		cursor->left = RemoveHelper(cursor->left, value);
		cursor->UpdateHeight();
		return cursor;
	}
	else {
		cursor->right = RemoveHelper(cursor->right, value);
		cursor->UpdateHeight();
		return cursor;
	}
}


//Prints the values stored in the tree from greatest to least
void AVLTree::InOrderTraversal() {
	std::cout << "In Order Traversal:" << std::endl;
	if (root) {
		InOrderHelper(root);
	}
	std::cout << std::endl;
}
void AVLTree::InOrderHelper(Node* cursor) {
	
	if (!cursor) {
		return;
	}

	else if (cursor->IsLeaf()) {
		std::cout << cursor->value << ", ";
	}

	else {
		InOrderHelper(cursor->left);
		std::cout << cursor->value << ", ";
		InOrderHelper(cursor->right);
	}
}

//Prints the values stored in the tree in PreOrder Form
void AVLTree::PreOrderTraversal() {
	if (root) {
		PreOrderHelper(root);
	}
	std::cout << std::endl;
}
void AVLTree::PreOrderHelper(Node* cursor) {
	if (!cursor) {
		return;
	}

	else if (cursor->IsLeaf()) {
		std::cout << cursor->value << ", ";
	}

	else {
		std::cout << cursor->value << ", ";
		PreOrderHelper(cursor->left);
		PreOrderHelper(cursor->right);
	}
}

void AVLTree::Print() {
	if (root) {
		std::cout << std::endl;
		std::string offset = "";
		PrintHelper(offset, root);
	}
}
void AVLTree::PrintHelper(std::string& offset, Node* cursor) {
	
	if (!cursor) {
		std::cout << offset << "[Empty]" << std::endl;
		return;
	}
	else {
		std::cout << offset << cursor->value << " ("
			<< cursor->height << ") ";

		if (cursor->IsLeaf()) {
			std::cout << "[leaf]";
		}
		std::cout << std::endl;


		if (cursor->left || cursor->right) {
			offset += "   ";
			PrintHelper(offset, cursor->left);
			PrintHelper(offset, cursor->right);
			offset.erase(offset.length() - 3, 3);
		}
	}
}

int AVLTree::Size() {
	if (root) {
		return SizeHelper(root);
	}
	else {
		return 0;
	}
}
int AVLTree::SizeHelper(Node* cursor) {
	if (!cursor) {
		return 0;
	}
	else {
		return 1 + SizeHelper(cursor->left) + SizeHelper(cursor->right);
	}
}

//returns a relative height value.  Positive means the right side is longer by that number of children
//Negative means the left side is longer by that number of children
int AVLTree::FindRelativeHeight(Node* cursor) {
	int left = -1;	
	int right = -1;
	if (cursor->left) {
		left = cursor->left->height;
	}
	if (cursor->right) {
		right = cursor->right->height;
	}
	return right - left;
}

///<summary>
///rebalance the tree through rotation patterns as described by Adelson-Velsky and Landis
///this routine ensures that no child chain is more than one node longer than its sibling's
///chain.
///</summary>
Node* AVLTree::RebalanceTree(Node* grandparent, int relativeHeightGrandParent) {
	//Find the relative heights necessary to determine the rotation sequence
	int rotateNumber = 0;
	int relativeHeightParent = 0;
	if (relativeHeightGrandParent > 0) {
		relativeHeightParent = FindRelativeHeight(grandparent->right);
	}
	else {
		relativeHeightParent = FindRelativeHeight(grandparent->left);
	}
	rotateNumber = relativeHeightGrandParent + relativeHeightParent;

	//apply the proper rotation sequence and return the correct root
	Node* root = nullptr;
	switch (rotateNumber) {
		//RIGHT rotation
	case -3: {
		Node* parent = grandparent->left;
		Node* child = parent->left;
		grandparent->left = parent->right;
		parent->right = grandparent;
		root = parent;
		grandparent->height -= 2;
		break;
	}

		//LEFT rotation, RIGHT rotation
	case -1: {
		Node* parent = grandparent->left;
		Node* child = parent->right;
		parent->right = child->left;
		child->left = parent;
		grandparent->left = child->right;
		child->right = grandparent;
		root = child;
		grandparent->height -= 2;
		parent->height -= 1;
		child->height += 1;
		break;
	}

		//RIGHT rotate, LEFT rotate
	case 1: {
		Node* parent = grandparent->right;
		Node* child = parent->left;
		parent->left = child->right;
		child->right = parent;
		grandparent->right = child->left;
		child->left = grandparent;
		root = child;
		grandparent->height -= 2;
		parent->height -= 1;
		child->height += 1;
		break;
	}

		//LEFT rotate
	case 3: {
		Node* parent = grandparent->right;
		Node* child = parent->right;
		grandparent->right = parent->left;
		parent->left = grandparent;
		root = parent;
		grandparent->height -= 2;
		break;
	}
	}

	return root;

}