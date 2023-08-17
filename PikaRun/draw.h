#ifndef DRAW_H
#define DRAW_H

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

void draw_movement() {
	if (!jumping)
	{
		iShowBMP2(pikachu_x_coordinate, pikachu_y_coordinate, pikachuRun[pikachuRunIndex], 0);
	}
	else
	{
		iShowBMP2(pikachu_x_coordinate, pikachu_y_coordinate, pikachuJump[pikachuJumpIndex], 0);
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
	//to display collected pokeballs
	iShowBMP2(width - 270, 590, box, 255);
	for (int i = 0, j = 0; i < pokeballCount; i++)
	{
		iShowBMP2(width - 265 + j, 610, balls, 0);
		j += 50;
	}
}

void draw_thunderbolt(){

	if (powerup)
	{
		iShowBMP2(pikachu_x_coordinate + 60, pikachu_y_coordinate - 10, thunderbolt[thunderboltIndex], 0);
	}
}

void draw_highscore(){

	iShowBMP(0, 0, highscore);
	iSetColor(0, 0, 0);
	for (int i = 0, j = 0; i < 5; i++)
	{
		iText(110, 400 - j, hs[i].name, GLUT_BITMAP_TIMES_ROMAN_24);
		iText(420, 400 - j, hs[i].score, GLUT_BITMAP_TIMES_ROMAN_24);
		j += 70;
	}
	iSetColor(255, 255, 255);
}
#endif