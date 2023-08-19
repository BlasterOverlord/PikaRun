#ifndef SCORE_H
#define SCORE_H

void recordScore(){
	fp = fopen("scores.txt", "a");
	if (fp == NULL)
		printf("The file could not be opened :(\n");
	else
	{
		fprintf(fp, "%s %s\n", name, scoreString);
		printf("Score recorded\n");
		fclose(fp);
	}
}

void readScore(){
	fp = fopen("scores.txt", "r");
	readIndex = 0;
	while (fscanf(fp, "%s %s", &hs[readIndex].name, &hs[readIndex].score) != EOF)
	{
		readIndex++;
	}
	fclose(fp);
}

void recordHighscore(){
	// sorting the hs[] array in descending order
	char temp[50];
	for (int i = 0; i < readIndex; i++)
	{
		for (int j = i + 1; j < readIndex; j++)
		{
			if (atoi(hs[i].score) < atoi(hs[j].score))
			{
				strcpy(temp, hs[j].score);
				strcpy(hs[j].score, hs[i].score);
				strcpy(hs[i].score, temp);

				strcpy(temp, hs[j].name);
				strcpy(hs[j].name, hs[i].name);
				strcpy(hs[i].name, temp);
			}
		}
	}
}

#endif