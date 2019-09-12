//FileName:		game.cpp
//Programmer:	Dan Cliburn
//Date:			9/1/2015
//Purpose:		This file defines the methods for the game class

#include "game.h"
#include "fort.h"
#include "Gingerbread.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
using namespace std;

Game::Game()
{
	srand(time(0));

	world = 0;
	rows = cols = 0;
}

void Game::setUpGame()
{
	int r, c;

	rows = 4;
	cols = 4;

	//Now we need to dynamically allocate world to be a 2D array of pointers to Locations
	world = new Location **[rows];
	for (r = 0; r < rows; r++)
	{
		world[r] = new Location *[cols];
	}

	//Next, go and initialize all of the pointers in the array to NULL
	for (r = 0; r < rows; r++)
	{
		for (c = 0; c < cols; c++)
		{
			world[r][c] = 0;
		}
	}

	//Now we need to place the player's fort (not on the first row or first column)
	r = rand() % (rows - 1) + 1;
	c = rand() % (cols - 1) + 1;
	world[r][c] = new Fort('F');

	for (int i = 0; i < 5; i++) //Place five crystals in the world
	{
		do
		{
			r = rand() % (rows - 1) + 1;
			c = rand() % cols;
		} while (world[r][c] != 0);
		world[r][c] = new Gingerbread('G');
	}

	//now put blank locations everywhere else.
	for (r = 0; r < rows; r++)
	{
		for (c = 0; c < cols; c++)
		{
			if (world[r][c] == 0) //nothing at this place yet
			{
				world[r][c] = new Location();
			}
		}
	}

	world[0][0]->setVisited(true);
	playerRow = 0;
	playerCol = 0;
}

//THE GAME CLASS version OF THE draw() METHOD IS NOT USED IN THIS LAB ACTIVITY
//For Project 8 you can just reuse the drawGame() method from your previous projects
//because it will never get called by the program.
void Game::drawGame()
{
	;
}

//THE GAME CLASS version OF THE playGame() METHOD IS NOT USED IN THIS LAB ACTIVITY
//For Project 8 you can just reuse the playGame() method from your previous projects
//because it will never get called by the program.
void Game::playGame()
{
	;
}

//THE GAME CLASS version OF THE instructions() METHOD IS NOT USED IN THIS LAB ACTIVITY
//For Project 8 you can just reuse the instructions() method from your previous projects
//because it will never get called by the program.
void Game::instructions()
{
	;
}

Game::~Game()
{
	int r, c;

	if (world != 0) //delete the world if it has been made to point to something
	{
		//first delete all of the objects
		for (r = 0; r < rows; r++)
		{
			for (c = 0; c < cols; c++)
			{
				delete world[r][c];
			}
		}

		//now delete all of the columns on each row
		for (r = 0; r < rows; r++)
		{
			delete[] world[r];
		}

		//finally, we can delete the array
		delete[] world;
	}
}