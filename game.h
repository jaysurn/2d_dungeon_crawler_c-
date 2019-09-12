//FileName:		game.h
//Programmer:	Dan Cliburn
//Date:			2/4/2013
//Purpose:		This file defines the header for the Game class

#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "location.h"

class Game
{
protected:
	Location ***world;
	Player p;

	int rows;
	int cols;
	int playerRow;
	int playerCol;

public:
	Game();

	//Required Methods
	void instructions();
	void setUpGame();
	void playGame();
	void drawGame();

	~Game();
};

#endif
