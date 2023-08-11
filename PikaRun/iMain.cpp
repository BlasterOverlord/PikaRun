#include <iostream>
#include "iGraphics.h"
#include "variables.h"

// function prototypes
void draw_homemenu();
void draw_movement();
void mute();
void draw_enemy();
void draw_pokeballs();
void draw_thunderbolt();

struct buttonCoordinate {
	int x, y;
} bCoordinate[3], exitButton;

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
    else if (gamestate == 1) 
	{
        iShowBMP(0, 0, highscore);
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
		if (gamestate == 0 && powerup == false && pokeballCount >= 5)
		{
			pokeballCount = 0;
			powerup = true;
		}
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

		pokeballIndex++;
		if (pokeballIndex >= 9)
			pokeballIndex = 0;

		thunderboltIndex++;
		if (thunderboltIndex >= 3)
			thunderboltIndex = 0;

		if (powerup)
		{
			timeWaste += 10;
			if (timeWaste >= 100)
			{
				powerup = false;
				timeWaste = 0;
			}
		}
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
		enemy[0].x -= enemySpeed;
		if (enemy[0].x < 0)
			enemy[0].x = width + (rand() % 1000);
		
		enemy[1].x -= enemySpeed;
		if (enemy[1].x < 0)
		{
			enemy[1].x = width + 100 + (rand() % 1500);
			enemy[1].y = height - 200 - (rand() % 200);
		}

		enemy[2].x -= enemySpeed;
		if (enemy[2].x < 0)
			enemy[2].x = width + 500 + (rand() % 2000);

		enemy[3].x -= enemySpeed;
		if (enemy[3].x < 0)
		{
			enemy[3].x = width + 500 + (rand() % 2000);
			enemy[3].y = height - 200 - (rand() % 200);
		}

		pokeballX -= 10;
		if (pokeballX <= 0)
		{
			pokeballX = width + 1500 + rand() % 3000;
			pokeballY = 150 + rand() % 250;
		}
	}
}

void draw_enemy() {
	iShowBMP2(enemy[0].x, enemy[0].y, rattata[enemy[0].index], 0);
	iShowBMP2(enemy[1].x, enemy[1].y, spearow[enemy[1].index], 0);
	iShowBMP2(enemy[2].x, enemy[2].y, meowth[enemy[2].index], 0);
	iShowBMP2(enemy[3].x, enemy[3].y, balloon, 0);
}

void draw_pokeballs() {
	iShowBMP2(pokeballX, pokeballY, pokeballs[pokeballIndex], 0);
	iShowBMP2(width - 270, 590, box, 255);
	for (int i = 0, j = 0; i < pokeballCount; i++)
	{
		iShowBMP2(width-265-j, 610, balls, 0);
		j -= 50;
	}
}

void setVariables(){
	enemy[0].x = width + 300;
	enemy[0].y = 100;
	enemy[1].x = width + 600;
	enemy[1].y = 400;
	enemy[2].x = width + 900;
	enemy[2].y = 100;
	enemy[3].x = width + 1800;
	enemy[3].y = 500;

	pokeballX = width;
	pokeballY = 250;
}

void updateScore(){
	if (gamestate == 0)
	{
		score++;
		sprintf(scoreString, "%d", score); //converts int to string
	}
}

void checkCollision(){
	
	if (gamestate == 0)
	{
		if ((pokeballX <= pikachu_x_coordinate + pikachu_width && pokeballX >= pikachu_x_coordinate-40) && (pikachu_y_coordinate <= pokeballY + pokeball_height/2 && pikachu_y_coordinate >= pokeballY))
		{
			pokeballX = width + 1500 + (rand() % 300);
			pokeballY = 150 + (rand() % 250);
			if (pokeballCount < 5)
				pokeballCount++;
		}

		for (int i = 0; i < enemy_count; i++)
		{
			if ((enemy[i].x <= pikachu_x_coordinate + pikachu_width && enemy[i].x >= pikachu_x_coordinate-40) && (enemy[i].y <= pikachu_y_coordinate + pikachu_height/2 && enemy[i].y >= pikachu_y_coordinate))
			{
				gamestate = 3;
			}
		}

		for (int i = 0; i < enemy_count; i++)
		{
			if (powerup == true && (enemy[i].x > pikachu_x_coordinate + 100 && enemy[i].x < width) && (enemy[i].y <= pikachu_y_coordinate + pikachu_height/2 && enemy[i].y >= pikachu_y_coordinate))
			{
				enemy[i].x = width + 500 + (rand() % 500);
			}
		}
	}

}

void draw_thunderbolt(){

	if (powerup)
	{
		iShowBMP2(pikachu_x_coordinate+60, pikachu_y_coordinate-10, thunderbolt[thunderboltIndex], 0);
	}
}

int main() {
	combined();
	buttonWork();
	setVariables();
	
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
