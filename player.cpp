//FileName:		player.cpp
//Programmer:	Jeff Wu
//Date:			12/05/2016
//Purpose:		This file defines the methods for the player class

#include "player.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

Player::Player(string n)
{
	name = n;
	age = 0;
	totalChristmas = 0;
}

void Player::setName(string n)
{
	name = n;
}

string Player::getName()
{
	return name;
}

void Player::display()
{
	cout << "Name: " << name << endl;
	cout << "Age: " << age << endl;
}

int Player::getInventoryItems(string &items)
{
	items = "";
	Item *current = inventory.getFirstElement();
	int total = 0;

	while (current != 0)
	{
		items += current->getName() + "\n";  //concatenate the name of the item onto items
		current = current->getNext();
		total++;
	}
	if (total == 0)  //only true if nothing in the inventory
	{
		items = "nothing";
	}

	return total;
}