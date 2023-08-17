#include <iostream>
#include "iGraphics.h"
#include "functions.h"	// contains function definitions/prototypes
#include "variables.h"	// global variables
#include "draw.h"		// functions that are being called from iDraw()
#include "score.h"		// score related functions
#include "keyboard.h"	// functions that are being called from iKeyboard() 
#include "timer.h"		// functions that are being used in iSetTimer()

using namespace std;

void iDraw() {
    
	iClear();
    if (gamestate == -1) 
	{
        draw_homemenu();
    }
    else if (gamestate == 0) 
	{
		if (playing)
		{
			for (int i = 0; i<70; i++)
			{
				iShowBMP(backGround[i].x, 0, Background[i]);
			}

			draw_thunderbolt();
			draw_movement();
			draw_enemy();
			draw_pokeballs();

			iText(20, 650, "Score:", GLUT_BITMAP_HELVETICA_18);
			iText(80, 650, scoreString, GLUT_BITMAP_HELVETICA_18);
		}
		else
		{
			iShowBMP(0, 0, nameScreen);
			iText(300, 500, name, GLUT_BITMAP_TIMES_ROMAN_24);
		}
    }
    else if (gamestate == 1) 
	{
		draw_highscore();
    }
    else if (gamestate == 2) 
	{
        iShowBMP(0, 0, ins);
    }
	else if (gamestate == 3)
	{
		iShowBMP(0, 0, gameover);
		iText(500, 100, "Score:", GLUT_BITMAP_HELVETICA_18);
		iText(560, 100, scoreString, GLUT_BITMAP_HELVETICA_18);
	}
}

void iMouseMove(int mx, int my) {
    if (mx < width - 20 && mx > 0 && my < height - 20 && my > 0) 
	{
        mposx = mx;
        mposy = my;
    }
}

void iMouse(int button, int state, int mx, int my) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
	{
        if (gamestate == -1)
		{
            bool buttonClicked = false;  // Flag to track if any button is clicked
			
            for (int i = 0; i < gamestate_limit; i++) 
			{

                if (gamestate >= -1 && gamestate <= 2 && mx >= bCoordinate[i].x && mx <= bCoordinate[i].x + button_width &&
                    my >= bCoordinate[i].y && my <= bCoordinate[i].y + button_height)
				{
                    gamestate = i;
                    buttonClicked = true;
					musicTracker = 1;
					if (musicOn == true && gamestate == 0)
					{
						PlaySound(music[musicTracker], NULL, SND_LOOP | SND_ASYNC);
					}
                    break;  
               }
            }
            
            if (!buttonClicked) 
			{
                gamestate = -1;  // Reset gamestate if no button is clicked
            }
            
            if (mx >= exitButton.x && mx <= exitButton.x + button_width &&
                my >= exitButton.y && my <= exitButton.y + button_height) 
			{
                exit(0);  // Exit the program when the exit button is clicked
            }
        }
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        // Handle right mouse button click
    }
}

void iPassiveMouseMove(int mx, int my) {
    mposx = mx;
    mposy = my;
}

void iKeyboard(unsigned char key) {
	
	returnToMainMenu(key); //returns gamestate to -1
	musicChange(key); // music change with l and k

    if (key == 'x') 
	{
		if (gamestate == 0 && powerup == false && pokeballCount >= 5)
		{
			pokeballCount = 0;
			powerup = true;
		}
    }
    if (key == 'm') 
	{
		if (gamestate == 0 && playing == false)
		{
			
		}
		else
			mute();
    }
	if (key == ' ')
	{
		if (jumping == false && playing == true)
		{
			jumping = true;
			jumpingUp = true;
		}
	}
	//name input
	nameInput(key);
}

void iSpecialKeyboard(unsigned char key) {
    if (key == GLUT_KEY_RIGHT) {
        // Handle right arrow key press
    }
    else if (key == GLUT_KEY_LEFT) {
        // Handle left arrow key press
    }
    if (key == GLUT_KEY_END) {
        exit(0);
    }
}

void setVariables(){
	
	pikachu_y_coordinate = ground;

	enemy[0].x = width + 300;
	enemy[0].y = ground;
	enemy[1].x = width + 600;
	enemy[1].y = 400;
	enemy[2].x = width + 900;
	enemy[2].y = ground;
	enemy[3].x = width + 1800;
	enemy[3].y = 500;

	pokeballX = width;
	pokeballY = 250;

	// for buttons
	int sum = height - 500;
	for (int i = gamestate_limit - 1; i >= 0; i--)
	{
		bCoordinate[i].x = 50;
		bCoordinate[i].y = sum;
		sum = sum + 150;
	}
	exitButton.x = 50;
	exitButton.y = height - 650;

	// for background
	int n = 0;
	for (int i = 0; i<70; i++)
	{
		backGround[i].x = n;
		n += 17;
	}
}

int main() {

	setVariables();
	readScore();
	recordHighscore();
	
    iSetTimer(150, changeIndex);
	iSetTimer(30, jump);
	iSetTimer(24, backchange);
	iSetTimer(5, checkCollision);
	iSetTimer(25, enemyMovement);
	iSetTimer(100, updateScore);

	if (musicOn && gamestate == -1)
		PlaySound(music[musicTracker], NULL, SND_LOOP | SND_ASYNC);

    iInitialize(width, height, "PikaRun");

    return 0;
}
