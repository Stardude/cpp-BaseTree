#pragma once
#include "Node.h"
class BaseTree : public Node
{
public:
	Node *root;
	Node *current;
	int height;
	int Base;

	BaseTree(int);

	void addElement(int);
	Node *searchElement(int);
	void splitNode(Node*);
	void deleteElement(int);
	void printTree(Node*, int);
};

