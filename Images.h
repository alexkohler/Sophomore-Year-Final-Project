//Images.h-image management
//Written by Alexander Kolher

#pragma once

#define	START_BUTTON 102
#define OPTIONS_BUTTON 103
#define	EXIT_BUTTON 106 
#define	DIFFICULTY_BUTTON 104
#define	AREA_BUTTON 105
#define	BACK_BUTTON 107
#define	SMALL_BUTTON 110
#define	LARGE_BUTTON 111
#define	NORMAL_BUTTON 108
#define	HARD_BUTTON	109
#define LEFT_WALL 97
#define RIGHT_WALL 96
#define BOTTOM_WALL 98
#define	TOP_WALL 99
#define WAIT_PERIOD 500

void loadSmall()
{
	dbSprite(RIGHT_WALL, 640, 0, 2);//loading vertical walls 
	dbSprite(LEFT_WALL, 0, 0, 2);//last ID establishes what image to load  
	dbSprite(BOTTOM_WALL, 0, 0, 3);
	dbSprite(TOP_WALL, 0, 470, 3);

}

void loadLarge()
{
	dbSprite(RIGHT_WALL, 880, 0, 18);
	dbSprite(LEFT_WALL, 0, 0, 18); //loading vertical walls
	dbSprite(BOTTOM_WALL, 0, 0, 17);
	dbSprite(TOP_WALL, 0, 580, 17);

}



void printAllSprites()
{
	dbSprite(START_BUTTON, 230, 150, 5);//size( 130x60)- start button
	dbSprite(OPTIONS_BUTTON, 230, 250, 6);//size(130x60)- options button 
	dbSprite(EXIT_BUTTON, 230, 350, 11); //exit button
	dbSprite(DIFFICULTY_BUTTON, 230, 150, 7); //load difficulty
	dbSprite(AREA_BUTTON, 380, 150, 8);//Area size
	dbSprite(BACK_BUTTON, 75, 150, 12);//load back button
	dbSprite(SMALL_BUTTON, 130, 100, 15); //load small
	dbSprite(LARGE_BUTTON, 360, 100, 16);//load large 
	dbSprite(NORMAL_BUTTON, 100, 250, 13); //load normal
	dbSprite(HARD_BUTTON, 365, 250, 14);//load hard
}

void loadImages()
{
	dbLoadImage("beginButton.bmp", 5); //load menu
	dbLoadImage("optionsButton.bmp", 6);//load options button
	dbLoadImage("difficultyButton.bmp", 7); //load difficulty button
	dbLoadImage("arenasizeButton.bmp", 8);
	dbLoadImage("normalButton.bmp", 9);//loading normal options button
	//dbLoadImage("backDropDefault.bmp", 10);
	dbLoadImage("exitButton.bmp", 11);
	dbLoadImage("backButton.bmp", 12);//back button 
	dbLoadImage("normal.bmp", 13);
	dbLoadImage("hard.bmp", 14);
	dbLoadImage("small.bmp", 15);
	dbLoadImage("large.bmp", 16);
	dbLoadImage("largehorizWall.bmp", 17);
	dbLoadImage("largeVerticalWall.bmp", 18);
	//dbSprite(200, 0, 0, 10);//background
}


void loadGameImages()
{
	dbLoadImage("Snake.bmp", 1); //load ID of 1, loads image into game
	dbLoadImage("VerticalWall.bmp", 2);
	dbLoadImage("HorizWall.bmp", 3);
	dbLoadImage("Food.bmp", 4);
	dbLoadImage("powerFood.bmp", 19);
}




void backButton()
{
	dbHideSprite(DIFFICULTY_BUTTON);//hide difficulty
	dbHideSprite(AREA_BUTTON); // hide area size
	dbHideSprite(BACK_BUTTON); //hide back button 
	dbShowSprite(START_BUTTON);
	dbShowSprite(OPTIONS_BUTTON);
	dbShowSprite(EXIT_BUTTON);


}

void hardButton()
{


	dbHideSprite(NORMAL_BUTTON);
	dbHideSprite(HARD_BUTTON);
	dbText(365, 200, "Hard Selected!");
	dbSyncRate(15);//change framerate to 30fps
	dbSync();
	dbWait(WAIT_PERIOD);
	dbShowSprite(DIFFICULTY_BUTTON);
	dbShowSprite(AREA_BUTTON);
	dbShowSprite(BACK_BUTTON);

}


void normalButton()
{
	dbHideSprite(NORMAL_BUTTON);
	dbHideSprite(HARD_BUTTON);

	dbText(100, 200, "Normal Selected!");
	dbSyncRate(10);//change framerate to 10fps (default for this game)
	dbSync();
	dbWait(WAIT_PERIOD);
	dbShowSprite(DIFFICULTY_BUTTON);
	dbShowSprite(AREA_BUTTON);
	dbShowSprite(BACK_BUTTON);
}

void difficultyButton()
{
	dbHideSprite(DIFFICULTY_BUTTON); //hide dif
	dbHideSprite(AREA_BUTTON); //hide size
	dbHideSprite(BACK_BUTTON); //hide back
	dbShowSprite(NORMAL_BUTTON);
	dbShowSprite(HARD_BUTTON);
}

void arenaButton()
{
	dbHideSprite(DIFFICULTY_BUTTON);//hide difficulty
	dbHideSprite(AREA_BUTTON);//hide size 
	dbHideSprite(BACK_BUTTON);//hide back
	dbShowSprite(SMALL_BUTTON);
	dbShowSprite(LARGE_BUTTON);

}

void optionsButton()
{
	dbHideSprite(START_BUTTON);
	dbHideSprite(OPTIONS_BUTTON);
	dbHideSprite(EXIT_BUTTON);
	dbShowSprite(DIFFICULTY_BUTTON);
	dbShowSprite(AREA_BUTTON);
	dbShowSprite(BACK_BUTTON);
}

void startButton()
{
	dbHideSprite(START_BUTTON);
	dbHideSprite(OPTIONS_BUTTON);
	dbHideSprite(EXIT_BUTTON);
}





void printScoreTime(double score)
{
	dbText(100, 100, "Score:");
	dbText(100, 119, "Time:");
	dbSetCursor(150, 100);
	dbPrint(score);

	dbText(150, 118, ":");
	dbSetCursor(160, 120);//set cursor for seconds
}



void menuDisplay()
{
	dbShowSprite(START_BUTTON);//show start
	dbShowSprite(OPTIONS_BUTTON);//show options
	dbShowSprite(EXIT_BUTTON);//show exit
	dbHideSprite(DIFFICULTY_BUTTON);//hide difficulty
	dbHideSprite(AREA_BUTTON);//hide arena size
	dbHideSprite(BACK_BUTTON);//hide back button
	dbHideSprite(SMALL_BUTTON); //hide small
	dbHideSprite(LARGE_BUTTON); //hide large
	dbHideSprite(NORMAL_BUTTON); //hide normal
	dbHideSprite(HARD_BUTTON); //hide hard 
}