//FileName:		Gingerbread.h
//Programmer:	Jeff Wu 
//Date:			12/05/2016
//Purpose:		This file defines the header for the Gingerbread class

#ifndef GINGERBREAD_H
#define GINGERBREAD_H

#include "location.h"

class Gingerbread : public Location
{
private:
	bool taken;

public:
	Gingerbread(char s = 'G');

	int visit(Player &p);
	void draw();

	void render(); //ADDED FOR THIS LAB ACTIVITY
}; //Do NOT forget this semicolon
#endif
