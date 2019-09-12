#ifndef ITEM_H
#define ITEM_H
#include <string>
using namespace std;

class Item
{
private:
	string name;
	Item * next;

public:
	Item(string n = "", Item *ptr = 0) { name = n; next = ptr; }

	void setName(string n) { name = n; }
	void setNext(Item *n) { next = n; }

	string getName() { return name; }
	Item *getNext() { return next; }
};

#endif