//FileName:		location.h
//Programmer:	Jeff Wu
//Date:			12/05/2016
//Purpose:		This file defines the header for the location class

#ifndef LOCATION_H
#define LOCATION_H

#include <string>
#include <iostream>
#include "player.h"
#include "LinkedList.h"
#include "item.h"
using namespace std;

class Location
{
protected:
	bool visited;
	char symbol;
	char answer;
	LinkedList ground;

public:
	Location(char s = ' ') { symbol = s; visited = false; }

	void setVisited(bool v) { visited = v; }
	void setSymbol(char s) { symbol = s; }

	bool getVisited() { return visited; }
	char getSymbol() { return symbol; }

	void putItemOnGround(Item *i); //places item back into the game board
	void checkforI(Player &p); //check if there is an item and if players want to pick it up

	virtual void draw() { if (visited) cout << symbol; else cout << "."; }
	virtual int visit(Player &p) { visited = true; return 1; }

	/*********** NEW  ***************/
	virtual void render(); //METHOD ADDED FOR THIS LAB ACTIVITY
						   //NOTE: You do NOT have to redefine render() in all of your Location subclasses.
						   //Only redefine it if you do not like how the default version works in location.cpp.
						   //For example, if you want to incorporate the notion of a "taken" variable to have
						   //the image appear based on whether or not the player has "taken" an item then you
						   //can override this method in the derived classes (see crystal.cpp for an example).
};

#endif