#ifndef KEYBOARD_H
#define KEYBOARD_H

void returnToMainMenu(unsigned char key){
	if (key == 'r')
	{
		if (gamestate == 3)
		{
			recordScore();
			readScore();
			recordHighscore();
		}
		if (gamestate == 0 && playing == false)
		{

		}
		else
		{
			//resets game
			gamestate = -1;
			playing = false;
			setVariables();
			musicTracker = 0;
			nameIndex = 0;
			name[nameIndex] = '\0';
			pokeballCount = 0, pokeballIndex = 0, score = 0;
			jumping = false, jumpingUp = false;
			pikachuRunIndex = 0, pikachuJumpIndex = 0;
			enemySpeed = 10, thunderboltIndex = 0, timeWaste = 0;
			powerup = false;
			srand(time(NULL));
			if (musicOn && gamestate == -1)
			{
				PlaySound(music[musicTracker], NULL, SND_LOOP | SND_ASYNC);
			}
		}
	}
}

void nameInput(unsigned char key){
	if (gamestate == 0 && playing == false)
	{
		if (key != '\b' && key != '\r' && key != ' ')
		{
			if (nameIndex >= name_limit - 1)
				nameIndex = name_limit - 1;
			else
			{
				name[nameIndex] = key;
				nameIndex++;
				name[nameIndex] = '\0';
			}
		}
		else if (key == '\b')
		{
			if (nameIndex <= 0)
				nameIndex = 0;
			else
			{
				nameIndex--;
				name[nameIndex] = '\0';
			}
		}
		else if (key == '\r')
		{
			playing = true;
		}
	}
}

void musicChange(unsigned char key){
	if (key == 'k')
	{
		if (gamestate == 0 && playing == false)
		{

		}
		else
		{
			if (musicTracker > 0 && musicTracker <= music_counter && musicOn == true)
			{
				musicTracker--;
				PlaySound(music[musicTracker], NULL, SND_LOOP | SND_ASYNC);
			}
		}

	}
	if (key == 'l')
	{
		if (gamestate == 0 && playing == false)
		{

		}
		else
		{
			if (musicTracker >= 0 && musicTracker < music_counter - 1 && musicOn == true)
			{
				musicTracker++;
				PlaySound(music[musicTracker], NULL, SND_LOOP | SND_ASYNC);
			}
		}

	}
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

#endif