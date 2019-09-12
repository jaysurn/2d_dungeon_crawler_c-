//FileName:		player.h
//Programmer:	Jeff Wu
//Date:			12/05/2016
//Purpose:		This file defines the header for the player class

#ifndef PLAYER_H
#define PLAYER_H

#include "LinkedList.h"
#include <string>
using namespace std;

class Player
{
protected: //attributes usually go here
	string name;
	int age;
	int totalChristmas;

	LinkedList inventory;

public:  //method prototypes usually go here
	Player(string n = "Jeff");

	//Set methods allow objects to change the attributes
	void setName(string n);
	void setAge(int a) { age = a; }
	void setTotalChristmas(int c) { totalChristmas = c; }

	//Get methods allow objects to tell us about their attributes
	string getName();
	int getAge() { return age; }
	int getTotalChristmas() { return totalChristmas; }

	//Functionality methods are additional actions of objects of the class
	void display();
	int getInventoryItems(string &items);
	Item *getInventoryItem(int i) { return inventory.find(i); }
	void takeItem(Item *i) { inventory.insert(i); }
	Item *dropItem(string name) { return inventory.remove(name); }
};

#endif