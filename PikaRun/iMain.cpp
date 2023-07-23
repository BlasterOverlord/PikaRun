#include <iostream>
#include <cstdlib> // For exit() function
#include "iGraphics.h"

#define width 1200
#define height 700
#define button_width 405
#define button_height 120
#define gamestate_limit 3
#define max_jump_limit 600
#define jumping_speed 25

// Global variables
int mposx = 200, mposy = 173, dx = 5, dy = 5;
int exitz = -1, hover = -1, gamestate = -1;
int pikachuRunIndex = 0, pikachuJumpIndex = 0;
int pikachuJumpCoordinate = 400;
bool musicOn = true;
int mute=1;
bool jumping = false, jumpingUp = false;

struct buttonCoordinate {
    int x, y;
} bCoordinate[3], exitButton;

struct obstacles {
	int x, y, index;
};

// Strings containing paths to files
char button[3][30] = { "images\\buttons\\play1.bmp", "images\\buttons\\score.bmp", "images\\buttons\\ins.bmp"};
char button2[3][30] = {"","",""};
char homemenu[30] = "images\\menu\\42_02.bmp";
char play[30] = "images\\menu\\play.bmp";
char score[30] = "images\\menu\\41.bmp";
char ins[30] = "images\\menu\\idk05.bmp";
char exitButtonImg[30] = "images\\buttons\\exit.bmp";
char pikachuRun[4][30] = {"images\\pikachu\\run1.bmp", "images\\pikachu\\run2.bmp", "images\\pikachu\\run3.bmp", "images\\pikachu\\run4.bmp"};
char pikachuJump[5][30] = {"images\\pikachu\\jump1.bmp", "images\\pikachu\\jump2.bmp", "images\\pikachu\\jump3.bmp", "images\\pikachu\\jump4.bmp", "images\\pikachu\\jump5.bmp"};

// function prototypes
void draw_homemenu();
void draw_movement();

 /*   char level_01[70][39] = {
    "images\\levels\\level_01\\row-1-column-1",
    "images\\levels\\level_01\\row-1-column-2",
    "images\\levels\\level_01\\row-1-column-3",
    "images\\levels\\level_01\\row-1-column-4",
    "images\\levels\\level_01\\row-1-column-5",
    "images\\levels\\level_01\\row-1-column-6",
    "images\\levels\\level_01\\row-1-column-7",
    "images\\levels\\level_01\\row-1-column-8",
    "images\\levels\\level_01\\row-1-column-9",
    "images\\levels\\level_01\\row-1-column-10",
    "images\\levels\\level_01\\row-1-column-11",
    "images\\levels\\level_01\\row-1-column-12",
    "images\\levels\\level_01\\row-1-column-13",
    "images\\levels\\level_01\\row-1-column-14",
    "images\\levels\\level_01\\row-1-column-15",
    "images\\levels\\level_01\\row-1-column-16",
    "images\\levels\\level_01\\row-1-column-17",
    "images\\levels\\level_01\\row-1-column-18",
    "images\\levels\\level_01\\row-1-column-19",
    "images\\levels\\level_01\\row-1-column-20",
    "images\\levels\\level_01\\row-1-column-21",
    "images\\levels\\level_01\\row-1-column-22",
    "images\\levels\\level_01\\row-1-column-23",
    "images\\levels\\level_01\\row-1-column-24",
    "images\\levels\\level_01\\row-1-column-25",
    "images\\levels\\level_01\\row-1-column-26",
    "images\\levels\\level_01\\row-1-column-27",
    "images\\levels\\level_01\\row-1-column-28",
    "images\\levels\\level_01\\row-1-column-29",
    "images\\levels\\level_01\\row-1-column-30",
    "images\\levels\\level_01\\row-1-column-31",
    "images\\levels\\level_01\\row-1-column-32",
    "images\\levels\\level_01\\row-1-column-33",
    "images\\levels\\level_01\\row-1-column-34",
    "images\\levels\\level_01\\row-1-column-35",
    "images\\levels\\level_01\\row-1-column-36",
    "images\\levels\\level_01\\row-1-column-37",
    "images\\levels\\level_01\\row-1-column-38",
    "images\\levels\\level_01\\row-1-column-39",
    "images\\levels\\level_01\\row-1-column-40",
    "images\\levels\\level_01\\row-1-column-41",
    "images\\levels\\level_01\\row-1-column-42",
    "images\\levels\\level_01\\row-1-column-43",
    "images\\levels\\level_01\\row-1-column-44",
    "images\\levels\\level_01\\row-1-column-45",
    "images\\levels\\level_01\\row-1-column-46",
    "images\\levels\\level_01\\row-1-column-47",
    "images\\levels\\level_01\\row-1-column-48",
    "images\\levels\\level_01\\row-1-column-49",
    "images\\levels\\level_01\\row-1-column-50",
    "images\\levels\\level_01\\row-1-column-51",
    "images\\levels\\level_01\\row-1-column-52",
    "images\\levels\\level_01\\row-1-column-53",
    "images\\levels\\level_01\\row-1-column-54",
    "images\\levels\\level_01\\row-1-column-55",
    "images\\levels\\level_01\\row-1-column-56",
    "images\\levels\\level_01\\row-1-column-57",
    "images\\levels\\level_01\\row-1-column-58",
    "images\\levels\\level_01\\row-1-column-59",
    "images\\levels\\level_01\\row-1-column-60",
    "images\\levels\\level_01\\row-1-column-61",
    "images\\levels\\level_01\\row-1-column-62",
    "images\\levels\\level_01\\row-1-column-63",
    "images\\levels\\level_01\\row-1-column-64",
    "images\\levels\\level_01\\row-1-column-65",
    "images\\levels\\level_01\\row-1-column-66",
    "images\\levels\\level_01\\row-1-column-67",
    "images\\levels\\level_01\\row-1-column-68",
    "images\\levels\\level_01\\row-1-column-69",
    "images\\levels\\level_01\\row-1-column-70",
};    */

void iDraw() {
    
	iClear();
    if (gamestate == -1) 
	{
        draw_homemenu();
    }
    else if (gamestate == 0) 
	{
		iShowBMP(0,0,play);
		draw_movement();
		
    }
    else if (gamestate == 1) 
	{
        iShowBMP(0, 0, score);
    }
    else if (gamestate == 2) 
	{
        iShowBMP(0, 0, ins);
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
void mute_mainmenu(int mute){
	if(mute%2==0){
        musicOn = false;
		if(!musicOn){
			PlaySound(0,0,0);}
		}
		else if(mute%2!=0){
			musicOn = true;
		if(musicOn){
			PlaySound("music\\pokemon.wav", NULL, SND_LOOP | SND_ASYNC);}
			
		}
}
void iKeyboard(unsigned char key) {
    if (key == 'w') {
        mposy += 50;
    }
    if (key == 's') {
        mposy -= 50;
    }
    if (key == 'd') {
        mposx += 50;
    }
    if (key == 'a') {
        mposx -= 50;
    }
    if (key == 'r') {
        gamestate = -1;
    }
    if (key == 'x') {
        exitz = 0;
    }
    if (key == 'm') {
        mute++;
		mute_mainmenu(mute);
	
    }
	if (key == ' ')
	{
		if (!jumping)
		{
			jumping = true;
			jumpingUp = true;
		}
	}
    
	/*else {
        musicOn = true;
        PlaySound("music\\old.wav", NULL, SND_ASYNC);
    }*/
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

void draw_homemenu() {
	
	iShowBMP(0, 0, homemenu);
    for (int i = 0; i < gamestate_limit; i++) 
	{
		if (mposx >= bCoordinate[i].x && mposx <= bCoordinate[i].x + button_width &&
            mposy >= bCoordinate[i].y && mposy <= bCoordinate[i].y + button_height) 
		{
            iShowBMP2(bCoordinate[i].x, bCoordinate[i].y, button[i], 255); // Hover effect
        } 
		else 
		{
            iShowBMP2(bCoordinate[i].x, bCoordinate[i].y, button[i], NULL);
        }
    }

    if (mposx >= exitButton.x && mposx <= exitButton.x + button_width &&
            mposy >= exitButton.y && mposy <= exitButton.y + button_height) 
	{
        iShowBMP2(exitButton.x, exitButton.y, exitButtonImg, 255); // Hover effect
    }
	else 
	{
        iShowBMP2(exitButton.x, exitButton.y, exitButtonImg, NULL);
    }
}


void index() {

	if (gamestate == 0 && jumping == false)
	{
		pikachuRunIndex++;
		
		if (pikachuRunIndex >= 4)
			pikachuRunIndex = 0;
	}
	else if (gamestate == 0 && jumping == true)
	{
		pikachuJumpIndex++;
		if (pikachuJumpIndex >= 5)
			pikachuJumpIndex = 0;
	}
}

void jump() {
	if (jumping)
	{
		if (jumpingUp)
		{
			pikachuJumpCoordinate += jumping_speed;
			if (pikachuJumpCoordinate > max_jump_limit)
				jumpingUp = false;
		}
		else
		{
			pikachuJumpCoordinate -= jumping_speed;
			if (pikachuJumpCoordinate <= 400)
			{
				jumping = false;
				pikachuJumpCoordinate = 400;
			}
		}
	}
}

void draw_movement() {
	if (!jumping)
	{
		iShowBMP2(200, 400, pikachuRun[pikachuRunIndex], 0);
	}
	else
	{
		iShowBMP2(200, pikachuJumpCoordinate, pikachuJump[pikachuJumpIndex], 0);
	}
}

void buttonWork() {
	int sum = height - 500;
    for (int i = gamestate_limit-1; i >= 0; i--)
	{
        bCoordinate[i].x = 50;
        bCoordinate[i].y = sum;
        sum = sum + 150;
    }

    exitButton.x = 50;
    exitButton.y = height - 650;
}

int main() {
	buttonWork();
    iSetTimer(100, index);
	iSetTimer(15, jump);

    if (musicOn)
        PlaySound("music\\pokemon.wav", NULL, SND_LOOP | SND_ASYNC);

    iInitialize(width, height, "PikaRun");

    return 0;
}
