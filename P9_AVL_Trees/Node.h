#ifndef __NODE__
#define __NODE__

#include "Observer.h"

class Node
{
public:
	Node(int value, Node* left, Node* right);
	~Node();
	bool IsLeaf();
	void UpdateHeight();

	int value;
	Node* left;
	Node* right;
	int height;
	Observer observer;	// needed for Unit Testing. Do Not Remove


  




};

#endif // __NODE__