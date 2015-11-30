#include "BaseTree.h"
#include <algorithm>

BaseTree::BaseTree(int _base) :
	Base(_base)
{
	root = new Node;
	current = new Node;
	current = root;
	height = 1;
}

void BaseTree::addElement(int data)
{
	if (current != root)
		current = searchElement(data);
	if (current->sons.size() != Base)
	{
		Node *tmp = new Node;
		tmp->data = data;
		tmp->parent = current;
		current->sons.push_back(tmp);
		if (current->sons.size() > 1)
		{
			sort(current->sons.begin(), current->sons.end(), [](const Node* a, const Node* b) { return a->data < b->data; });
			current->keys.clear();
			for (int i = 0; i < current->sons.size() - 1; i++)
				current->keys.push_back(current->sons[i + 1]->data);
		}
	}
	else
	{
		splitNode(current);
		addElement(data);
	}
}

Node * BaseTree::searchElement(int data)
{
	Node *tmp = root;
	for (int i = 0; i < tmp->keys.size(); i++)
	{
		if (i == 0 && data < tmp->keys[i])
		{
			tmp = tmp->sons[i];
			i = -1;
		}
		else if (i + 1 != tmp->keys.size())
		{
			if (data >= tmp->keys[i] && data < tmp->keys[i + 1])
			{
				tmp = tmp->sons[i + 1];
				i = -1;
			}
		}
		else if (i == tmp->keys.size() - 1 && data >= tmp->keys[i])
		{
			tmp = tmp->sons[i + 1];
			i = -1;
		}
		if (tmp->sons.size() == 0) break;
	}
	return tmp->parent;
}

void BaseTree::splitNode(Node *current)
{
	Node *left = new Node;
	for (int i = 0; i < current->sons.size() / 2; i++)
	{
		left->sons.push_back(current->sons[i]);
		left->sons[i]->parent = left;
		if (i != current->sons.size() / 2 - 1)
			left->keys.push_back(current->keys[i]);
	}

	Node *right = new Node;
	for (int i = current->sons.size() / 2, j = 0; i < current->sons.size(); i++, j++)
	{
		right->sons.push_back(current->sons[i]);
		right->sons[j]->parent = right;
		if (i != current->sons.size() - 1)
			right->keys.push_back(current->keys[i]);
	}
	int key;
	if (Base % 2 == 1) key = current->keys[current->keys.size() / 2 - 1];
	else key = current->keys[current->keys.size() / 2];
	if (current == root)
	{
		root = new Node;
		root->keys.push_back(key);
		root->sons.push_back(left);
		root->sons.push_back(right);
		left->parent = root;
		right->parent = root;
		height++;
	}
	else
	{
		current->parent->keys.push_back(key);
		for (int i = 0; i < current->parent->sons.size(); i++)
		{
			if (current->parent->sons[i] == current)
			{
				current->parent->sons.erase(current->parent->sons.begin() + i);
				break;
			}
		}
		current->parent->sons.push_back(left);
		current->parent->sons.push_back(right);
		sort(current->parent->sons.begin(), current->parent->sons.end(), [](const Node* a, const Node* b) { return a->keys[0] < b->keys[0]; });
		sort(current->parent->keys.begin(), current->parent->keys.end());
		left->parent = current->parent;
		right->parent = current->parent;
		if (current->parent->sons.size() > Base)
			splitNode(current->parent);
	}
}

void BaseTree::deleteElement(int data)
{
	current = searchElement(data);
	int j = INT16_MAX;
	for (int i = 0; i < current->sons.size(); i++)
	{
		if (current->sons[i]->data == data)
		{
			j = i;
			break;
		}
	}
	if (j == INT16_MAX) { cout << "There is no such an element...\n"; return; }
	current->sons.erase(current->sons.begin() + j);
	if (j != 0)
	{
		current->keys.erase(current->keys.begin() + j - 1);
		if (current->sons.size() == 1)
		{
			data = current->sons[0]->data;
			for (int i = 0; i < current->parent->keys.size(); i++)
				if (current->parent->keys[i] == data)
				{
					current->parent->keys.erase(current->parent->keys.begin() + i);
					current->parent->sons.erase(current->parent->sons.begin() + i + 1);
					break;
				}
			delete current;
			addElement(data);
		}
	}
	else if (j == 0)
	{
		current->keys.erase(current->keys.begin());
		int key = current->sons[0]->data;
		bool p = false;
		Node *tmp = current;
		while (!p)
		{
			p = false;
			for (int i = 0; i < tmp->parent->keys.size(); i++)
			{
				if (tmp->parent->keys[i] == data)
				{
					p = true;
					tmp->parent->keys[i] = key;
					break;
				}
			}
			if (!p)
				tmp = tmp->parent;
		}
	}
}

void BaseTree::printTree(Node *current, int height)
{
	if (current->data != 0)
	{
		for (int i = 0; i < height; i++)
		{
			cout << "\t";
		}
		cout << current->data << "\n";
		return;
	}
	for (int i = current->sons.size() - 1; i >= 0; i--)
	{
		if (i != current->sons.size() - 1)
		{
			for (int j = 0; j < height; j++)
			{
				cout << "\t";
			}
			cout << current->keys[i] << "\n\n";
		}
		printTree(current->sons[i], height + 1);
	}
}