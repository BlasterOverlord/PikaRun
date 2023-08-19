#ifndef TIMER_H
#define TIMER_H

void changeIndex() {

	//for pikachu
	if (gamestate == 0 && jumping == false && playing == true)
	{
		pikachuRunIndex++;

		if (pikachuRunIndex >= 4)
			pikachuRunIndex = 0;
	}
	else if (gamestate == 0 && jumping == true && playing == true)
	{
		pikachuJumpIndex++;
		if (pikachuJumpIndex >= 5)
			pikachuJumpIndex = 0;
	}

	// for obstacles
	if (gamestate == 0 && playing == true)
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

		//for pokeball
		pokeballIndex++;
		if (pokeballIndex >= 9)
			pokeballIndex = 0;

		// for powerup
		thunderboltIndex++;
		if (thunderboltIndex >= 3)
			thunderboltIndex = 0;

		// to make sure that thunderbolt stays long enough on the screen
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
			if (pikachu_y_coordinate <= ground)
			{
				jumping = false;
				pikachu_y_coordinate = ground;
			}
		}
	}
}

void backchange(){
	if (gamestate == 0 && playing == true)
	{
		for (int i = 0; i<70; i++)
		{
			backGround[i].x -= 17;

			if (backGround[i].x <= 0)
				backGround[i].x = width;
		}
	}
}

void enemyMovement(){

	if (gamestate == 0 && playing == true)
	{
		for (int i = 0; i < enemy_count; i++)
		{
			enemy[i].x -= enemySpeed;
			if (enemy[i].x <= 0)
			{
				if (i == 0)
				{
					enemy[i].x = width + (rand() % 1000);
				}
				if (i == 1)
				{
					enemy[i].x = width + 400 + (rand() % 1000);
					enemy[i].y = height - 200 - (rand() % 200);
				}
				if (i == 2)
				{
					enemy[i].x = width + 800 + (rand() % 1500);
				}
				if (i == 3)
				{
					enemy[i].x = width + 1000 + (rand() % 2000);
					enemy[i].y = height - 200 - (rand() % 200);
				}

			}
		}

		// for pokeball
		pokeballX -= 10;
		if (pokeballX <= 0)
		{
			pokeballX = width + 500 + (rand() % 1000);
			pokeballY = 150 + rand() % 250;
		}
	}
}

void checkCollision(){

	if (gamestate == 0 && playing == true)
	{
		//pokeball
		if ((pokeballX <= pikachu_x_coordinate + pikachu_width && pokeballX >= pikachu_x_coordinate - pokeball_width) && (pikachu_y_coordinate <= pokeballY + pokeball_height && pikachu_y_coordinate >= pokeballY - pikachu_height))
		{
			pokeballX = width + 500 + (rand() % 1000);
			pokeballY = 150 + (rand() % 250);
			if (pokeballCount < 5)
				pokeballCount++;
		}

		//obstacles
		for (int i = 0; i < enemy_count; i++)
		{
			if ((enemy[i].x <= pikachu_x_coordinate + pikachu_width && enemy[i].x >= pikachu_x_coordinate - enemy_width) && (pikachu_y_coordinate <= enemy[i].y + enemy_height && pikachu_y_coordinate >= enemy[i].y - pikachu_height))
			{
				gamestate = 3;
			}
		}

		//powerup
		for (int i = 0; i < enemy_count; i++)
		{
			if (powerup == true && (enemy[i].x > pikachu_x_coordinate + pikachu_width && enemy[i].x < width) && (pikachu_y_coordinate <= enemy[i].y + enemy_height && pikachu_y_coordinate >= enemy[i].y - pikachu_height))
			{
				enemy[i].x = width + 500 + (rand() % 1000);
				score += 100;
			}
		}
	}

}

void updateScore(){
	if (gamestate == 0 && playing == true)
	{
		score++;
		sprintf(scoreString, "%d", score); //converts int to string
	}

	if (score > 500 && score < 1000)
		enemySpeed = 15;
	else if (score > 1000 && score < 1500)
		enemySpeed = 20;
	else if (score > 1500 && score < 2000)
		enemySpeed = 25;
	else if (score > 2000)
		enemySpeed = 30;
}

#endif