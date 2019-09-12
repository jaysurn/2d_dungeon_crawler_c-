//FileName:		linkedList.h
//Programmer:	Dan Cliburn
//Date:			1/16/2013
//Purpose:		This file defines the header for a LinkedList class

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "item.h"
#include <string>
using namespace std;

class LinkedList
{
private:
	Item *head;

public:
	LinkedList() { head = 0; }

	void insert(Item *p);
	Item *remove(string key);
	Item *find(int itemNum);
	Item *find(string key);
	Item *getFirstElement() { return head; }
	int listLength();

	~LinkedList();
};

#endif