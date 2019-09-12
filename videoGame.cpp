//FileName:		Videogame.cpp
//Programmer:	Dan Cliburn
//Date:			11/21/2016
//Purpose:		This file defines the methods for the Videogame class
//See:  http://www.sdltutorials.com/sdl-tutorial-basics/
//		http://www.sdltutorials.com/sdl-opengl-tutorial-basics/
//		http://www.sdltutorials.com/sdl-soundbank
//for many more details on how to write an OpenGL program using SDL.
//You might also want to go to these pages which will link you to other tutorials on how to do stuff with SDL.
//Be warned, however, that a lot of the tutorials describe SDL 1.2, but we will be using SDL 2 in this lab.

#include "videogame.h"
#include "texture.h"
#include "LinkedList.h"
#include <SDL.h>
#include <Windows.h>  //Must include this here to get it to compile
//#include <gl/gl.h>
//#include <gl/glu.h>
#include <glut.h>  //includes gl.h and glu.h
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

const int MONITORWIDTH = 800;
const int MONITORHEIGHT = 600;

//Static class variables
string Videogame::message1 = "";
string Videogame::message2 = "";
string Videogame::message3 = "";

Videogame::Videogame()
{
	message1 = "";
	message2 = "";
	message3 = "";
}

//Initializes SDL and OpenGL
bool Videogame::init()
{
	display = NULL;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		return false;
	}

	if ((display = SDL_CreateWindow("Lab 20 Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, MONITORWIDTH, MONITORHEIGHT, SDL_WINDOW_OPENGL)) == NULL)
	{
		return false;
	}
	oglcontext = SDL_GL_CreateContext(display);

	glClearColor(0.3, 0.3, 0.3, 1.0);  //Will be the color of the background

									   //Set parameters for how we want to view the scene
	glViewport(0, 0, MONITORWIDTH, MONITORHEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//Create a view frustum whose aspect ratio matches that of the window 
	double aspectRatio = ((double)(MONITORWIDTH)) / ((double)(MONITORHEIGHT));
	glFrustum(-0.1, 0.1, -0.1 / aspectRatio, 0.1 / aspectRatio, 0.1, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Do OpenGL init stuff
	glEnable(GL_DEPTH_TEST);
	glLineWidth(1.0); //Controls the thickness of lines

					  //Now, initialize our other variables for drawing the game
	Eye[0] = Aim[0] = cols / 2.0;
	Eye[2] = 1.28*rows;
	Aim[2] = rows / 2.0;
	Eye[1] = rows / 2.0;
	Aim[1] = 0.0;
	Up[0] = 0.0;
	Up[1] = 1.0;
	Up[2] = 0.0;

	//TODO: You need to make sure you use the same letter below as you assigned to the classes
	//in the game's setUpGame() method. For example, in setUpGame() the Fort object is assigned
	//the character 'F' for its symbol so the EXACT SAME letter needs to be sent below to the 
	//loader so that OpenGL knows to associate the fort.bmp image with the Fort class.
	Texture loader;
	loader.loadTexBMP("images//fort.bmp", (int)('F'), addAlpha);  //Image for the fort
	loader.loadTexBMP("images//crystal.bmp", (int)('C'), addAlpha);  //Image for the crystal
																	 //TODO: Load more textures here for your other Location derived classes

																	 //NOTE: The image for the player should be loaded after you have loaded all of your images
																	 //for the locations. This ensures that the player image is assigned a texture ID different
																	 //than all of your location classes (which is what glGenTextures does).
	glGenTextures(1, &playerTexID);
	loader.loadTexBMP("images//player.bmp", playerTexID, addAlpha);  //Image for the player	

	return true;  //Everything got initialized
}

//Method to draw an image associated with texID
void Videogame::renderBitMap(int texID)
{
	// make sure the transparent part of the texture isn't drawn
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0);

	// select the texture
	glColor3f(1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, texID);
	glBegin(GL_QUADS);
	// bottom left corner
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);

	// bottom right corner
	glTexCoord2f(1.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);

	// top right corner
	glTexCoord2f(1.0, 1.0);
	glVertex3f(1.0, 1.0, 0.0);

	// top left corner
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0, 1.0, 0.0);
	glEnd();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
}

//Draws the Heads Up Display (HUD) that shows players' info
void Videogame::drawHUD()
{
	unsigned int i;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//Create a view frustum whose aspect ratio matches that of the window 
	double aspectRatio = ((double)(MONITORWIDTH)) / ((double)(MONITORHEIGHT));
	int width = 260;  //TODO:  Make this bigger if you need more space for your messages
	int height = width / aspectRatio;
	glOrtho(0, width, 0, height, -10, 10);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(1.0, 1.0, 1.0);  //COLOR OF THE TEXT MESSAGES
	glPushMatrix();
	glTranslatef(0.0, .95*height, 0.0);
	glScalef(0.05, 0.05, 0.05);
	for (i = 0; i < message1.length(); i++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, message1[i]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, .90*height, 0.0);
	glScalef(0.05, 0.05, 0.05);
	for (i = 0; i < message2.length(); i++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, message2[i]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, .85*height, 0.0);
	glScalef(0.05, 0.05, 0.05);
	for (i = 0; i < message3.length(); i++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, message3[i]);
	glPopMatrix();

	//Put the program back in the proper projection for drawing the rest of the game
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-0.1, 0.1, -0.1 / aspectRatio, 0.1 / aspectRatio, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//This method draws the map of the world that the user sees
void Videogame::drawGame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//Establish the eye and aim positions, and the up vector 
	//The analogy is that of holding a digital camera and pointing it at what you want to take a picture of:
	//Eye is where the camera is at
	//Aim is what the camera is pointed at
	//Up is a vector that defines the up direction
	//NOTE: you do not need to change these parameters for Project 8
	gluLookAt(Eye[0], Eye[1], Eye[2], Aim[0], Aim[1], Aim[2], Up[0], Up[1], Up[2]);

	//Go through each location and render what the user should see
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			if (playerRow == r && playerCol == c) //Is this the square the player is at?
			{
				glColor3f(0.1, 0.8, 0.1);  //If so, then draw this square a different color
			}
			else
			{
				glColor3f(0.1, 0.4, 0.1); //color for ground locations the player has visited
			}
			if (world[r][c]->getVisited() == true || (playerRow == r && playerCol == c))
			{
				//Player has been to or is currently at this spot
				//Draw the green square that makes up the ground at a visited location
				glBegin(GL_QUADS);
				glVertex3f(c, 0.0, r);
				glVertex3f(c, 0.0, r + 1.0);
				glVertex3f(c + 1.0, 0.0, r + 1.0);
				glVertex3f(c + 1.0, 0.0, r);
				glEnd();

				//Now render what the player should see at this location
				glPushMatrix(); //Save the current transformation state
				glTranslatef(c, 0, r + 0.7);
				world[r][c]->render(); //Go render the appropriate image (if any) for this location
				glPopMatrix();
			}
		}
	}

	//Now render the Player's Bitmap Image
	glPushMatrix(); //Save the current transformation state
	glTranslatef(playerCol, 0, playerRow + 0.3);
	renderBitMap(playerTexID);
	glPopMatrix();

	//Draw the text messages. HUD stands for Heads Up Display
	drawHUD();

	SDL_GL_SwapWindow(display);
}

//This method handles user key presses on the keyboard
bool Videogame::handleEvent(SDL_Event *theEvent)
{
	switch (theEvent->type)
	{
	case SDL_QUIT:  //User clicks on the 'X' in the Window
	{
		endGame();
		exit(0);
	}
	case SDL_KEYDOWN:
	{
		if (theEvent->key.keysym.sym == SDLK_DOWN && playerRow < rows - 1)
		{
			playerRow++;
		}
		//TODO: Add code so that the user can move left, right, and up
		else if (theEvent->key.keysym.sym == SDLK_LEFT && playerCol > 0)
		{
			playerCol--;
		}
		else if (theEvent->key.keysym.sym == SDLK_RIGHT && playerCol < cols - 1)
		{
			playerCol++;
		}
		else if (theEvent->key.keysym.sym == SDLK_UP && playerRow > 0)
		{
			playerRow--;
		}
		//TODO: ADD CODE TO SUPPORT OTHER TYPES OF KEY PRESSES
		else if (theEvent->key.keysym.sym == SDLK_i)
		{
			string inventory;
			int totalItems;
			totalItems = p.getInventoryItems(inventory); //NEW METHOD FOR PROJECT 8
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Inventory", inventory.c_str(), NULL);

			if (totalItems > 0) //Player has items he/she can drop
			{
				//First we need to ask users if they want to drop something 
				Item *item;
				//Three things must be specifed for each button: an SDL flag (or the number 0), 
				//the ID number to be returned if the button is selected, and the text for the button
				const SDL_MessageBoxButtonData buttons[2] = {
					{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "NO" }, //button with ID 0
					{ 0, 1, "YES" } //button with ID 1
				}; //NOTE that the buttons appear in the REVERSE order of how they are specified above
				const SDL_MessageBoxData messageboxdata = { SDL_MESSAGEBOX_INFORMATION,
					NULL,
					"Inventory",
					"Do you want to drop an item?",
					SDL_arraysize(buttons),
					buttons,
					NULL
				};
				//NOTE that the first parameter can be: SDL_MESSAGEBOX_ERROR, SDL_MESSAGEBOX_WARNING, or SDL_MESSAGEBOX_INFORMATION
				int answer;
				SDL_ShowMessageBox(&messageboxdata, &answer); //answer will hold the ID of the pressed button
				if (answer == 1) //The user must have pressed the "YES" button, so they want to drop something
				{
					//Now we need to build the message box with the list of items in the inventory as the buttons, plus a cancel button
					const int MAX_INVENTORY_SIZE = 7;  //TODO: Make this the maximum number of collectable items in your game + one
					SDL_MessageBoxButtonData buttonData[MAX_INVENTORY_SIZE];
					char buttonNames[MAX_INVENTORY_SIZE][20]; //This will hold the names of each of the buttons
					for (int i = totalItems; i > 0; i--)
					{
						buttonData[i].flags = 0;
						buttonData[i].buttonid = i;
						item = p.getInventoryItem(i - 1); //NEW METHOD FOR PROJECT 8. Index in the inventory will be one less than i (since we have an extra button, the CANCEL button)
						if (item != 0)  //This should always be true, but we'll check it just in case
						{
							strcpy_s(buttonNames[i], item->getName().c_str()); //Copies the item name into the buttonNames text array
							buttonData[i].text = buttonNames[i]; //now place the item name into the buttonData array
						}
						else
							buttonData[i].text = "OOPS"; //Hopefully this never happens
					}
					//Finally, create a "CANCEL" button to show up last in the message box (index 0) just in case the user changes his/her mind about dropping an item
					buttonData[0].flags = SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT;
					buttonData[0].buttonid = 0;
					buttonData[0].text = "CANCEL";

					//We can now present the message box to the user
					const SDL_MessageBoxData messageboxdata2 = { SDL_MESSAGEBOX_INFORMATION,
						NULL,
						"Inventory",
						"Click on the item you want to drop",
						totalItems + 1,
						buttonData,
						NULL
					};
					SDL_ShowMessageBox(&messageboxdata2, &answer); //answer will hold the ID of the pressed button, which will be the button representing the item the user wants to drop

					if (answer != 0) //The user must have selected one of the items and NOT the CANCEL button (since answer would be 0 if the user clicked on CANCEL)
					{
						item = p.getInventoryItem(answer - 1);  //Find the item that corresponds with answer, remember that item numbers are one off from actual position in the list
						if (item != 0) //This should always be true, but we'll check just in case
						{
							item = p.dropItem(item->getName()); //Now, remove the item from the player's inventory
							if (item != 0) //Again this should always be true, but just in case
							{
								world[playerRow][playerCol]->putItemOnGround(item);  //Insert the item onto the ground list at this location
							}
						}
					}
				}
			}
		}
		else
		{
			message3 = "You can't do that!";
			drawGame();
			Sleep(1000); //Show the error message for one second
		}
		return true;
	}
	}
	return false; //was not a KEYDOWN event
}

//This method controls the game
void Videogame::playGame()
{
	int state = 1;

	instructions(); //Tell the player how to play the game
	setUpGame();  //call setUpGame() from the Game class

	if (!init()) //This function (defined above) sets up OpenGL and SDL
	{
		cout << "Not everything was initialized" << endl;
		return;
	}

	SDL_Event events;  //Makes an SDL_Events object that we can use to handle events
	SDL_PollEvent(&events); //This initializes the events object
	while (p.getTotalChristmas() < 5) //the game continues as long as the player has not found four crystals
	{
		//Build message strings for the HUD (Head's Up Display)
		message1 = p.getName() + ", use the arrow keys to move.";
		stringstream out2;
		out2 << p.getTotalChristmas();
		message2 = "You have found " + out2.str() + " items";
		drawGame(); //draw the current state of the game

		do
		{
			SDL_WaitEvent(&events); //wait here until there is an event to handle
		} while (handleEvent(&events) == false); //keep looping if event was something other than a KEYDOWN 
		drawGame(); //update the user's position on the gameboard

					//reset message strings and resolve actions involved with the move
		message1 = message2 = message3 = "";
		state = world[playerRow][playerCol]->visit(p);
		//TODO: This might be a good place to check to see if something is on the ground here (PROJECT 8 requirement)
		world[playerRow][playerCol]->checkforI(p);

	}
	message1 = "You found all five Items!";
	drawGame(); //Draw the game one last time before the program ends
	Sleep(4000); //pause for 4 seconds before ending the game
	endGame();
	system("pause");
}

void Videogame::instructions()
{
	//In this example we use the SDL_ShowSimpleMessageBox function to display instructions to the user. 
	//See: https://wiki.libsdl.org/SDL_ShowSimpleMessageBox
	string message = "Welcome to the exciting game of Find the Fort.\nIn this game you use the arrow keys to navigate around on the game board to find the fort.\n";
	message += "If you find the fort you will get a ticket to an exciting University of the Pacific sporting event.\n";
	message += "In this version of the game, there are also crystals to find. Once you find all five crystals the\ngame ends. Have fun!";
	string title = "Find the Fort";
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, title.c_str(), message.c_str(), NULL);
	//NOTE that the first parameter can be: SDL_MESSAGEBOX_ERROR, SDL_MESSAGEBOX_WARNING, or SDL_MESSAGEBOX_INFORMATION

	//Check to see if the user wants to play. Here we will use the SDL_ShowMessageBox function which allows the programmer to
	//specify his/her own buttons. See: https://wiki.libsdl.org/SDL_ShowMessageBox
	title = "Question?";
	message = "Do you want to play?";
	//Three things must be specifed for each button: an SDL flag (or the number 0), the ID number to be returned if the button is selected, and the text for the button
	const SDL_MessageBoxButtonData buttons[3] = {
		{ SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "CANCEL" }, //button with ID 2
		{ 0, 1, "NO" }, //button with ID 1
		{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "YES" } //button with ID 0
	}; //NOTE that the buttons appear in the REVERSE order of how they are specified above
	const SDL_MessageBoxData messageboxdata = { SDL_MESSAGEBOX_INFORMATION, NULL, title.c_str(), message.c_str(), SDL_arraysize(buttons), buttons, NULL };
	//NOTE that the first parameter can be: SDL_MESSAGEBOX_ERROR, SDL_MESSAGEBOX_WARNING, or SDL_MESSAGEBOX_INFORMATION
	int answer;
	do
	{
		SDL_ShowMessageBox(&messageboxdata, &answer); //answer will hold the ID of the pressed button
		if (answer == 1) //The user must have pressed the "NO" button
		{
			endGame();
			exit(0);
		}
		else if (answer == 2 || answer == -1) //The user must have pressed the "CANCEL" button or closed the Window
		{
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Uh oh!", "You have to select YES or NO", NULL);
		}
	} while (answer != 0); //Loop until the user selects to play since the ID for "YES" is 0

						   //We can still use the console to get input from the user until our graphics window is created (which happens as soon as this method ends).
	string name;
	cout << "Please enter your name: ";
	cin >> name;
	p.setName(name);
}

void Videogame::endGame()
{
	SDL_GL_DeleteContext(oglcontext);
	SDL_DestroyWindow(display);
	SDL_Quit();
}