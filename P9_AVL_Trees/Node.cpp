#include "Node.h"


Node::Node(int value, Node* left, Node* right) {
	this->value = value;
	this->left = left;
	this->right = right;
	this->UpdateHeight();
}

Node::~Node() {

}

///<summary>
///postcondition: returns true if it is a leaf, which means that there are no
///children. returns false if there are one or more child nodes
///</summary>
bool Node::IsLeaf() {
	if ((left == nullptr) && (right == nullptr)) {
		return true;
	}

	else {
		return false;
	}
}
//During insertion and removal the height will be updated
void Node::UpdateHeight() {
	int maxHeight = 0;
	//check the children for the maximum height
	if (left || right) {
		if (left) {
			maxHeight = left->height;
		}
		if (right) {
			if (right->height > maxHeight) {
				maxHeight = right->height;
			}
			//height of the node is one higher than the max of its children
		}
		height = ++maxHeight;
	}
	//no children, no height
	else {
		height = 0;
	}

}