//FileName:		present.h
//Programmer:	Ryan Su 
//Purpose:		This file defines the header for the present class

#pragma once

#include "location.h"

class Present : public Location
{
private:
	bool taken;

public:
	Present(char s = 'P');

	int visit(Player &p);
	void draw();

	void render(); 
}; 