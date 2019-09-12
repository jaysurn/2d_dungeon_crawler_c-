//FileName:		Gingerbread.cpp
//Programmer:	Jeff Wu
//Date:			12/05/2016
//Purpose:		This file defines the methods for the Gingerbread class

#include "Gingerbread.h"
#include "videoGame.h"
#include "item.h"
#include <SDL.h> //need to include this since we are using SDL_ShowMessageBox

Gingerbread::Gingerbread(char s)
	: Location(s) //: Location(s) passes the parameter s to the base
{				//class constructor (in this case, Location) 
	taken = false; //initialize class specific attributes here
}


void Gingerbread::draw()
{
	if (visited == true && taken == false)
		cout << symbol;
	else if (taken == true)
		cout << " ";
	else
		cout << ".";
}

int Gingerbread::visit(Player &p)
{
	if (taken == false)
	{
		//taken = true;
		//cout << "You found a magic crystal" << endl;

		//Here we call the SDL_ShowMessageBox function which allows the programmer to
		//specify his/her own buttons. See: https://wiki.libsdl.org/SDL_ShowMessageBox
		string title = "You found a Gingerbread.";
		string message = "What do you want to do?";
		//Three things must be specifed for each button: an SDL flag (or the number 0), the ID number to be returned if the button is selected, and the text for the button
		string buttonNames[2] = { "Take Gingerbread", "Leave Gingerbread" };
		const SDL_MessageBoxButtonData buttons[2] = {
			{ 0, 1, buttonNames[1].c_str() }, //button with ID 1
			{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, buttonNames[0].c_str() } //button with ID 0
		}; //NOTE that the buttons appear in the REVERSE order of how they are specified above
		const SDL_MessageBoxData messageboxdata = { SDL_MESSAGEBOX_INFORMATION, NULL, title.c_str(), message.c_str(), SDL_arraysize(buttons), buttons, NULL };
		//NOTE that the first parameter can be: SDL_MESSAGEBOX_ERROR, SDL_MESSAGEBOX_WARNING, or SDL_MESSAGEBOX_INFORMATION
		int answer;
		SDL_ShowMessageBox(&messageboxdata, &answer); //answer will hold the ID of the pressed button
		if (answer == 0) //The user must have pressed the "Take Gingerbread" button
		{
			taken = true;
			p.setTotalChristmas(p.getTotalChristmas() + 1);
			Item *i = new Item("Gingerbread");
			p.takeItem(i);
		}
	}
	visited = true;
	return 1;
}

void Gingerbread::render()
{
	//Only render the picture for this location if we have been here (visited == true)
	//but we did not "Take Gingerbread" (taken == false)
	if (visited == true && taken == false)
	{
		Videogame::renderBitMap((int)(symbol));
	}
}