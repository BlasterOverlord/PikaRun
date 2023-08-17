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
			enemy[2].x = width + 500 + (rand() % 1500);

		enemy[3].x -= enemySpeed;
		if (enemy[3].x < 0)
		{
			enemy[3].x = width + 1000 + (rand() % 2000);
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

void checkCollision(){

	if (gamestate == 0 && playing == true)
	{
		if ((pokeballX <= pikachu_x_coordinate + pikachu_width && pokeballX >= pikachu_x_coordinate - 40) && (pikachu_y_coordinate <= pokeballY + pokeball_height / 2 && pikachu_y_coordinate >= pokeballY))
		{
			pokeballX = width + 1000 + (rand() % 500);
			pokeballY = 150 + (rand() % 250);
			if (pokeballCount < 5)
				pokeballCount++;
		}

		for (int i = 0; i < enemy_count; i++)
		{
			if ((enemy[i].x <= pikachu_x_coordinate + pikachu_width && enemy[i].x >= pikachu_x_coordinate - pikachu_width) && (enemy[i].y <= pikachu_y_coordinate + pikachu_height && enemy[i].y >= pikachu_y_coordinate))
			{
				gamestate = 3;
			}
		}

		//powerup
		for (int i = 0; i < enemy_count; i++)
		{
			if (powerup == true && (enemy[i].x > pikachu_x_coordinate + 100 && enemy[i].x < width) && (enemy[i].y <= pikachu_y_coordinate + pikachu_height / 2 && enemy[i].y >= pikachu_y_coordinate))
			{
				enemy[i].x = width + 500 + (rand() % 500);
			}
		}
	}

}

#endif