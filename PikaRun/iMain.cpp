#include <iostream>
//#include <cstdlib> // For exit() function
#include "iGraphics.h"

#define width 1100
#define height 674
#define button_width 405
#define button_height 120
#define gamestate_limit 3
#define pikachu_x_coordinate 300
#define max_jump_limit 300
#define jumping_speed 25
#define music_counter 3
#define highest_music_tracker_number (music_counter-2)
#define enemy_count 4

// Global variables
int mposx = 200, mposy = 173, dx = 5, dy = 5;
int exitz = -1, hover = -1, gamestate = -1;
int pikachuRunIndex = 0, pikachuJumpIndex = 0;
int pikachu_y_coordinate = 100;
bool musicOn = true;
bool jumping = false, jumpingUp = false;
int musicTracker = 0;
int score = 0;
char scoreString[12];

struct buttonCoordinate {
    int x, y;
} bCoordinate[3], exitButton;

// Strings containing paths to files
char button[3][30] = { "images\\buttons\\play1.bmp", "images\\buttons\\score.bmp", "images\\buttons\\ins.bmp"};
char button2[3][30] = {"","",""};
char homemenu[30] = "images\\menu\\42_02.bmp";
char play[30] = "images\\menu\\play.bmp";
char highscore[30] = "images\\menu\\41.bmp";
char ins[30] = "images\\menu\\idk05.bmp";
char exitButtonImg[30] = "images\\buttons\\exit.bmp";
char pikachuRun[4][30] = {"images\\pikachu\\run1.bmp", "images\\pikachu\\run2.bmp", "images\\pikachu\\run3.bmp", "images\\pikachu\\run4.bmp"};
char pikachuJump[5][30] = {"images\\pikachu\\jump1.bmp", "images\\pikachu\\jump2.bmp", "images\\pikachu\\jump3.bmp", "images\\pikachu\\jump4.bmp", "images\\pikachu\\jump5.bmp"};
char music[music_counter][50] = { "music\\pokemon.wav", "music\\PokemonWorld.wav", "music\\champion.wav"};

//obstacles
struct obstacles {
	int x, y, index;
} enemy[enemy_count];

char rattata[6][30] = {"images\\obstacles\\rat\\1.bmp", "images\\obstacles\\rat\\2.bmp", "images\\obstacles\\rat\\3.bmp", "images\\obstacles\\rat\\4.bmp", "images\\obstacles\\rat\\5.bmp", "images\\obstacles\\rat\\6.bmp"};
char spearow[4][31] = { "images\\obstacles\\spearow\\1.bmp", "images\\obstacles\\spearow\\2.bmp", "images\\obstacles\\spearow\\3.bmp", "images\\obstacles\\spearow\\4.bmp"};
char meowth[5][30] = { "images\\obstacles\\meowth\\1.bmp", "images\\obstacles\\meowth\\2.bmp", "images\\obstacles\\meowth\\3.bmp", "images\\obstacles\\meowth\\4.bmp", "images\\obstacles\\meowth\\5.bmp"};
char balloon[30] = "images\\obstacles\\balloon.bmp";

/*
enemy[0] is rattata (common)
enemy[1] is spearow (common)
enemy[2] is meowth (rare)
enemy[3] is balloon (rare)
*/

// function prototypes
void draw_homemenu();
void draw_movement();
void mute();
void draw_enemy();

char Background[70][30] = {
	"images\\plz\\image01.bmp",
	"images\\plz\\image02.bmp",
	"images\\plz\\image03.bmp",
	"images\\plz\\image04.bmp",
	"images\\plz\\image05.bmp",
	"images\\plz\\image06.bmp",
	"images\\plz\\image07.bmp",
	"images\\plz\\image08.bmp",
	"images\\plz\\image09.bmp",
	"images\\plz\\image10.bmp",
	"images\\plz\\image11.bmp",
	"images\\plz\\image12.bmp",
	"images\\plz\\image13.bmp",
	"images\\plz\\image14.bmp",
	"images\\plz\\image15.bmp",
	"images\\plz\\image16.bmp",
	"images\\plz\\image17.bmp",
	"images\\plz\\image18.bmp",
	"images\\plz\\image19.bmp",
	"images\\plz\\image20.bmp",
	"images\\plz\\image21.bmp",
	"images\\plz\\image22.bmp",
	"images\\plz\\image23.bmp",
	"images\\plz\\image24.bmp",
	"images\\plz\\image25.bmp",
	"images\\plz\\image26.bmp",
	"images\\plz\\image27.bmp",
	"images\\plz\\image28.bmp",
	"images\\plz\\image29.bmp",
	"images\\plz\\image30.bmp",
	"images\\plz\\image31.bmp",
	"images\\plz\\image32.bmp",
	"images\\plz\\image33.bmp",
	"images\\plz\\image34.bmp",
	"images\\plz\\image35.bmp",
	"images\\plz\\image36.bmp",
	"images\\plz\\image37.bmp",
	"images\\plz\\image38.bmp",
	"images\\plz\\image39.bmp",
	"images\\plz\\image40.bmp",
	"images\\plz\\image41.bmp",
	"images\\plz\\image42.bmp",
	"images\\plz\\image43.bmp",
	"images\\plz\\image44.bmp",
	"images\\plz\\image45.bmp",
	"images\\plz\\image46.bmp",
	"images\\plz\\image47.bmp",
	"images\\plz\\image48.bmp",
	"images\\plz\\image49.bmp",
	"images\\plz\\image50.bmp",
	"images\\plz\\image51.bmp",
	"images\\plz\\image52.bmp",
	"images\\plz\\image53.bmp",
	"images\\plz\\image54.bmp",
	"images\\plz\\image55.bmp",
	"images\\plz\\image56.bmp",
	"images\\plz\\image57.bmp",
	"images\\plz\\image58.bmp",
	"images\\plz\\image59.bmp",
	"images\\plz\\image60.bmp",
	"images\\plz\\image61.bmp",
	"images\\plz\\image62.bmp",
	"images\\plz\\image63.bmp",
	"images\\plz\\image64.bmp",
	"images\\plz\\image65.bmp",
	"images\\plz\\image66.bmp",
	"images\\plz\\image67.bmp",
	"images\\plz\\image68.bmp",
	"images\\plz\\image69.bmp",
	"images\\plz\\image69.bmp"

};

struct background{
	int x;
};
background backGround[70];



void iDraw() {
    
	iClear();
    if (gamestate == -1) 
	{
        draw_homemenu();
    }
    else if (gamestate == 0) 
	{
		for (int i = 0; i<70; i++){

			iShowBMP(backGround[i].x, 0, Background[i]);
		}

		draw_movement();
		draw_enemy();

		iText(20, 650, "Score:", GLUT_BITMAP_HELVETICA_18);
		iText(80, 650, scoreString, GLUT_BITMAP_HELVETICA_18);
    }
    else if (gamestate == 1) 
	{
        iShowBMP(0, 0, highscore);
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

                if (gamestate >= -1 && gamestate < gamestate_limit && mx >= bCoordinate[i].x && mx <= bCoordinate[i].x + button_width &&
                    my >= bCoordinate[i].y && my <= bCoordinate[i].y + button_height)
				{
                    gamestate = i;
                    buttonClicked = true;
					musicTracker = 1;
					if (musicOn == true && gamestate == 0)
					{
						PlaySound(music[1], NULL, SND_LOOP | SND_ASYNC);
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

    if (key == 'r') {
		gamestate = -1;
		musicTracker = 0;
		if (musicOn && gamestate == -1){
			PlaySound(music[musicTracker], NULL, SND_LOOP | SND_ASYNC);
			musicTracker = 0;
		}
    }
	if (key == 'k') {
		if (musicTracker > 0  && musicTracker <= music_counter && musicOn == true){
			musicTracker--;
			PlaySound(music[musicTracker], NULL, SND_LOOP | SND_ASYNC);
		}

	}
	if (key == 'l') {
		if (musicTracker >= 0 && musicTracker < music_counter-1 && musicOn == true){
			musicTracker++;
			PlaySound(music[musicTracker], NULL, SND_LOOP | SND_ASYNC);
		}

	}
    if (key == 'x') {
        
    }
    if (key == 'm') {
		mute();
    }
	if (key == ' ')
	{
		if (!jumping)
		{
			jumping = true;
			jumpingUp = true;
		}
	}
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


void changeIndex() {

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

	if (gamestate == 0)
	{
		enemy[0].index++;
		if (enemy[0].index >= 6)
			enemy[0].index = 0;

		enemy[1].index++;
		if (enemy[1].index >= 4)
			enemy[1].index = 0;

		enemy[2].index++;
		if (enemy[2].index >= 5)
			enemy[2].index = 0;
	}
}

void jump() {
	if (jumping)
	{
		if (jumpingUp)
		{
			pikachu_y_coordinate += jumping_speed;
			if (pikachu_y_coordinate > max_jump_limit)
				jumpingUp = false;
		}
		else
		{
			pikachu_y_coordinate -= jumping_speed;
			if (pikachu_y_coordinate <= 100)
			{
				jumping = false;
				pikachu_y_coordinate = 100;
			}
		}
	}
}

void draw_movement() {
	if (!jumping)
	{
		iShowBMP2(pikachu_x_coordinate, 100, pikachuRun[pikachuRunIndex], 0);
	}
	else
	{
		iShowBMP2(pikachu_x_coordinate, pikachu_y_coordinate, pikachuJump[pikachuJumpIndex], 0);
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

void mute() {
	if (musicOn)
	{
		musicOn = false;
		PlaySound(0, 0, 0);
	}
	else
	{
		musicOn = true;
		PlaySound(music[musicTracker], NULL, SND_LOOP | SND_ASYNC);
	}
}
void combined(){
	int n = 0;
	for (int i = 0; i<70; i++)
	{

		backGround[i].x = n;
		n += 17;
	}
}
void backchange(){
	for (int i = 0; i<70; i++){
		backGround[i].x -= 17;

		if (backGround[i].x <= 0)
			backGround[i].x = width;
	}
}

void enemyMovement(){
	
	if (gamestate == 0)
	{
		enemy[0].x -= 10;
		if (enemy[0].x < 0)
			enemy[0].x = width + (rand() % 300);
		
		enemy[1].x -= 10;
		if (enemy[1].x < 0)
		{
			enemy[1].x = width + 100 + (rand() % 400);
			enemy[1].y = height - 200 - (rand() % 200);
		}

		enemy[2].x -= 10;
		if (enemy[2].x < 0)
			enemy[2].x = width + 100 + (rand() % 500);

		enemy[3].x -= 10;
		if (enemy[3].x < 0)
		{
			enemy[3].x = width + 200 + (rand() % 600);
			enemy[3].y = height - 200 - (rand() % 200);
		}
	}
}

void draw_enemy() {
	iShowBMP2(enemy[0].x, enemy[0].y, rattata[enemy[0].index], 0);
	iShowBMP2(enemy[1].x, enemy[1].y, spearow[enemy[1].index], 0);
	iShowBMP2(enemy[2].x, enemy[2].y, meowth[enemy[2].index], 0);
	iShowBMP2(enemy[3].x, enemy[3].y, balloon, 0);
}

void setEnemyVariables(){
	enemy[0].x = width + 300;
	enemy[0].y = 90;
	enemy[1].x = width + 400;
	enemy[1].y = 400;
	enemy[2].x = width + 600;
	enemy[2].y = 90;
	enemy[3].x = width + 800;
	enemy[3].y = 500;
}

void updateScore(){
	if (gamestate == 0)
	{
		score++;
		sprintf(scoreString, "%d", score);
	}
}

int main() {
	combined();
	buttonWork();
	setEnemyVariables();
	
    iSetTimer(100, changeIndex);
	iSetTimer(30, jump);
	iSetTimer(24, backchange);
	iSetTimer(25, enemyMovement);
	iSetTimer(100, updateScore);

	if (musicOn && gamestate == -1)
		PlaySound(music[musicTracker], NULL, SND_LOOP | SND_ASYNC);

    iInitialize(width, height, "PikaRun");

    return 0;
}
