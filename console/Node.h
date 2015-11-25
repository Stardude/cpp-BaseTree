#pragma once
#include<vector>
#include<iostream>
using namespace std;

class Node
{
public:
	vector<Node*> sons;
	vector<int> keys;
	int data;
	Node *parent;

	Node();
};

