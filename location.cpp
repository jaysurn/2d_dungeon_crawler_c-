//FileName:		location.cpp
//Programmer:	Dan Cliburn
//Date:			9/11/2015
//Purpose:		This file defines the methods for the location class

#include "location.h"
#include "videoGame.h"

//This method defines how to draw whatever we want to see for objects of this class
void Location::render()
{
	if (visited == true && symbol != ' ') //We have been to this spot and it is not a default location
	{
		//We are using the "symbol" as the texture ID.  Since 
		//"symbol" is a char, it must be casted to an int
		Videogame::renderBitMap((int)(symbol));
	}
}

void Location::putItemOnGround(Item *i) {
	visited = true;
	ground.insert(i);//insert item into the linklist inventory
	symbol = ground.getFirstElement()->getName()[0];//place symbol of dropped item on the board
}


void Location::checkforI(Player &p) {
	if (ground.getFirstElement() != NULL) {
		//taken = true;
		//cout << "You found a magic crystal" << endl;

		//Here we call the SDL_ShowMessageBox function which allows the programmer to
		//specify his/her own buttons. See: https://wiki.libsdl.org/SDL_ShowMessageBox
		string title = "You found a crystal";
		string message = "What do you want to do?";
		//Three things must be specifed for each button: an SDL flag (or the number 0), the ID number to be returned if the button is selected, and the text for the button
		string buttonNames[2] = { "Take crystal", "Leave crystal" };
		const SDL_MessageBoxButtonData buttons[2] = {
			{ 0, 1, buttonNames[1].c_str() }, //button with ID 1
			{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, buttonNames[0].c_str() } //button with ID 0
		}; //NOTE that the buttons appear in the REVERSE order of how they are specified above
		const SDL_MessageBoxData messageboxdata = { SDL_MESSAGEBOX_INFORMATION, NULL, title.c_str(), message.c_str(), SDL_arraysize(buttons), buttons, NULL };
		//NOTE that the first parameter can be: SDL_MESSAGEBOX_ERROR, SDL_MESSAGEBOX_WARNING, or SDL_MESSAGEBOX_INFORMATION
		int answer;
		SDL_ShowMessageBox(&messageboxdata, &answer); //answer will hold the ID of the pressed button
		if (answer == 0) //The user must have pressed the "Take crystal" button
		{
			//taken = true;
			p.setTotalChristmas(p.getTotalChristmas() + 1);
			Item *i = new Item("crystal");
			p.takeItem(i);
		}

	}
}