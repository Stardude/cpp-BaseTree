#include "BaseTree.h"
#include<iostream>
using namespace std;

int main()
{
	int base;
	char m;
m:	cout << "Enter the base of tree (4 is minimum) -> "; cin >> base;
	if (base < 4) { cout << "Reenter, please...\n"; goto m; }
	BaseTree ob(base);
	cout << "\nEnter elements (0-exit):\n";
	int data;
	while (1)
	{
		cout << "-> "; cin >> data;
		if (data == 0) break;
		ob.addElement(data);
	}
	system("cls");
	cout << "Original tree:\n\n\n";
	ob.printTree(ob.root, 0);
	char choise;
	bool p = false;
	while(1)
	{
		cout << "\nDo you want to delete an element? (y/n) -> ";
		cin >> choise;
		if (choise == 'n') break;
		else if (choise == 'y')
		{
			p = true;
			cout << "Enter an element -> "; cin >> data;
			ob.deleteElement(data);
		}
	}
	if (p)
	{
		cout << "\n\nTree after removing:\n\n\n";
		ob.printTree(ob.root, 0);
	}
	cout << "\n\n";
	system("pause");
	return 1;
}