//FileName:		videoGame.h
//Programmer:	Dan Cliburn
//Date:			9/15/2015
//Purpose:		This file defines the header for the Videogame class
//We will use OpenGL (www.opengl.org) and SDL (www.libsdl.org) for the game


#ifndef VIDEOGAME_H
#define VIDEOGAME_H

#include "game.h"
#include <SDL.h>
#include <Windows.h> //Must include this here to get it to compile
#include <GL/GLU.h>

class Videogame : public Game
{
private:
	//SDL and other Graphics variables
	SDL_Window *display;
	SDL_GLContext oglcontext;
	GLuint playerTexID;

	//Variables to handle player movement
	double Eye[3], Aim[3], Up[3];

	//Variables to manage the Heads Up Display (HUD) display
	static string message1;
	static string message2;
	static string message3;

public:
	Videogame();

	static void setMessage1(string s) { message1 = s; }
	static void setMessage2(string s) { message2 = s; }
	static void setMessage3(string s) { message3 = s; }
	static string getMessage1() { return message1; }
	static string getMessage2() { return message2; }
	static string getMessage3() { return message3; }

	bool init();  //sets up both SDL and OpenGL

	void playGame();
	void drawGame();
	void instructions();
	void checkGround();

	static void renderBitMap(int texID);
	bool handleEvent(SDL_Event *theEvent);
	void drawHUD();
	void endGame();
};

#endif