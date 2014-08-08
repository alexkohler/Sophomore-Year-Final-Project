//Dark GDK Tutorial- main entry point
//Written by Alexander Kohler 
#include <vector>
#include "darkGDK.h"//Dark GDK's 'iostream'
#include "Images.h"
#include "Tools.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>//for getline
#include <stdlib.h>
using namespace std;

#define	BUTTON_WIDTH 130
#define BUTTON_HEIGHT 60
#define BLOCK_SIZE 30
#define BUTTON_START_X 230
#define BUTTON_START_Y 150
#define	HIGHSCORES "scores.txt"
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
#define SCREEN_LARGE_X	900
#define	SCREEN_LARGE_Y	600	
#define SCREEN_SMALL_X	660	
#define SCREEN_SMALL_Y	480
#define COLOR_DEPTH	32
#define WAIT_PERIOD 500

enum gamestate_t {game, menu, exitGame};//enumeration for gamestate
enum screenstate_t {Small, Large};//enumeration for screenstate 
enum menustate_t {initialmenu, options, difficulty, areaSize, areaSmall};//enumeration for menustate

void DarkGDK(void)
{
	int scoreIncrement = 20;//not a constant, will be changed if a powerup is picked p

	double score=0;
	gamestate_t gamestate;
	gamestate = menu; //initially at menu


	screenstate_t screenstate;
	screenstate = Large; //default large screen

	menustate_t menustate;
	//menustate = initialmenu;
	vector<double> prevScoreVector;
	for (int i=0; i<3; i++)
	{
		prevScoreVector.push_back(0);
	}
	//setting up the game-initialization functions
	dbSyncOn();//turns Sync on so we can manipulate fps
	dbSyncRate(10);//average fps
	dbDisableEscapeKey(); //reserves escape key 




	if (screenstate == Large)
		dbSetDisplayMode(SCREEN_LARGE_X, SCREEN_LARGE_Y, COLOR_DEPTH); //large display mode(change in options, will also have to load different walls depending on which is chosen which can be determined via a boolean), rand food function will change too 
	else 
		dbSetDisplayMode (SCREEN_SMALL_X ,SCREEN_SMALL_Y, COLOR_DEPTH);
	dbSetImageColorKey(255, 0, 255); //any color with pink in background will be turned transparent 



	int mx; //mouse x position
	int my; //mouse y position

	loadImages();
	menustate = initialmenu;
	dbDrawSpritesFirst();
	printAllSprites();
	loadImages();

	while (LoopGDK() && gamestate == menu){
		if (gamestate==menu){


			int click = dbMouseClick();
			mx = dbMouseX();
			my = dbMouseY();


			switch (menustate){
			case initialmenu:
				menuDisplay();
				dbShowSprite(START_BUTTON);
				dbShowSprite(OPTIONS_BUTTON);
				dbShowSprite(EXIT_BUTTON);
				break;

			case options:
				dbShowSprite(DIFFICULTY_BUTTON);
				dbShowSprite(AREA_BUTTON);
				dbShowSprite(BACK_BUTTON);//showing options, diffi, and exit
				dbHideSprite(START_BUTTON);
				dbHideSprite(OPTIONS_BUTTON);
				dbHideSprite(EXIT_BUTTON);
				dbHideSprite(SMALL_BUTTON);
				dbHideSprite(LARGE_BUTTON);
				dbHideSprite(NORMAL_BUTTON);
				dbHideSprite(HARD_BUTTON);
				break;


			case difficulty:	
				dbHideSprite(START_BUTTON);
				dbHideSprite(OPTIONS_BUTTON);
				dbHideSprite(EXIT_BUTTON);//hiding difficulty, area size and back
				dbShowSprite(NORMAL_BUTTON);
				dbShowSprite(HARD_BUTTON);//loading normal and hard
				break;


			case areaSize:
				dbHideSprite(START_BUTTON);
				dbHideSprite(OPTIONS_BUTTON);
				dbHideSprite(EXIT_BUTTON); //hiding difficulty, area size and back
				dbShowSprite(SMALL_BUTTON);
				dbShowSprite(LARGE_BUTTON);//loading small and large
				break;
			}





			if (mx > BUTTON_START_X && mx < BUTTON_START_X + BUTTON_WIDTH && my > BUTTON_START_Y && my < BUTTON_START_Y + BUTTON_HEIGHT && menustate == initialmenu) //clicking start button
			{
				if (click ==1 ){
					startButton();
					gamestate = game;
				}
			}

			if (mx > 230 && mx < 230 + BUTTON_WIDTH && my > 250 && my< 250 + BUTTON_HEIGHT && menustate == initialmenu)// clicking options button 
			{
				if (click == 1)
				{
					menustate = options;
					optionsButton();
				}
			}

			if ( mx > 230 && mx < 230 + BUTTON_WIDTH && my > 350 && my < 350 + BUTTON_HEIGHT && menustate == initialmenu)//clicking exit or back button
			{	

				if (click==1){
					gamestate = exitGame;
					break;
				}


			}

			if (mx > 380 && mx < 380 + BUTTON_WIDTH && my > 150 && my< 150 + BUTTON_HEIGHT && menustate == options)// clicking arena size (same coords as options button) 
			{
				if (click == 1)
				{
					menustate = areaSize;
					arenaButton();
				}
			}


			if (mx > 230 && mx < 230 + BUTTON_WIDTH && my > 150 && my< 150 + BUTTON_HEIGHT && menustate == options)//clicking difficulty (same coords as start)
			{
				if (click ==1){
					menustate = difficulty;
					difficultyButton();
				}

			}

			if ( mx > 75 && mx < 75 + BUTTON_WIDTH && my > 150 && my < 150 + BUTTON_HEIGHT && menustate == options)//clicking back button
			{

				if (click==1){
					menustate = initialmenu;
					backButton();
				}

			}


			if (mx > 130 && mx < 130 + BUTTON_WIDTH && my > 100 && my< 100 + BUTTON_HEIGHT && menustate == areaSize)// clicking small (same coords as nothing)
			{
				if (click ==1){
					dbText(130, 75, "Small Selected!");
					dbSync();
					dbWait(WAIT_PERIOD);
					if (screenstate == Large){
						dbSetDisplayMode (SCREEN_SMALL_X ,SCREEN_SMALL_Y, COLOR_DEPTH);
						dbSetWindowSize (SCREEN_SMALL_X, SCREEN_SMALL_Y);
						screenstate = Small;
						loadImages();
						printAllSprites(); //reload assets 
					}
					dbHideSprite(SMALL_BUTTON);
					dbHideSprite(LARGE_BUTTON);
					menustate = options;
					dbShowSprite(DIFFICULTY_BUTTON);
					dbShowSprite(AREA_BUTTON);
					dbShowSprite(BACK_BUTTON);
					int check;
					check = dbSpriteExist(DIFFICULTY_BUTTON);
				}

			}

			if (mx > 360 && mx < 360 + BUTTON_WIDTH && my > 100 && my< 100 + BUTTON_HEIGHT && menustate == areaSize){// clicking large (same coords as nothing)
				if (click==1){
					//menuDepth = 1;
					dbText(360, 75, "Large selected!");
					dbSync();
					dbWait(WAIT_PERIOD);
					if (screenstate == Small){
						dbSetDisplayMode (SCREEN_LARGE_X, SCREEN_LARGE_Y, COLOR_DEPTH);
						dbSetWindowSize(SCREEN_LARGE_X, SCREEN_LARGE_Y);
						screenstate = Large;
						loadImages();
						printAllSprites();
					}
					menustate = options;
					dbShowSprite(DIFFICULTY_BUTTON);
					dbShowSprite(AREA_BUTTON);
					dbShowSprite(BACK_BUTTON);
					//dbSync();
				}
			}




			if (mx > 100 && mx < 100 + BUTTON_WIDTH && my > 250 && my< 250 + BUTTON_HEIGHT && menustate == difficulty)//clicking normal
			{
				if (click ==1){
					menustate = options;
					normalButton();
				}

			}


			if (mx > 365 && mx < 365 + BUTTON_WIDTH && my > 250 && my< 250 + BUTTON_HEIGHT && menustate == difficulty)//clicking hard
			{
				if (click ==1){
					menustate = options;
					hardButton();

				}
			}




			if (dbEscapeKey() == 1) //looks to see if escape key is pressed, returns one if pressed
			{
				break; //break from the loop and terminate game
			}
			dbSync();
		}



		loadGameImages();
		enum direction_t {right, down, left, up};
		direction_t direction;
		direction = up;//initially moving up
		int segmentSize=1;
		double timeS=0;//time in seconds
		double timeM=0; //time in minutes;
		int x=300;
		int y=300;
		dbSprite(1, x, y, 1); //loading snake
		dbHideSprite(1);
		if (screenstate == Small){//load small components of screen 
			loadSmall();
		}
		if (screenstate == Large)
		{
			loadLarge();
		}
		for (int z=96; z<100; z++)//deleting walls
			dbHideSprite(z);

		dbSprite(101, 400, 200, 4); //loading food for testing purposes 
		dbHideSprite(101);
		int i=1;
		int j=0;//incrementer for seconds
		int k=0;//incrementer for minutes
		int previousX[50];
		int previousY[50];//room for 50 segments 
		score = 0; //reset score


		while(LoopGDK() && gamestate==game)// Says we're going to use DarkGDK in this while loop
		{

			dbShowSprite(1);
			dbShowSprite(101);
			for (int j=96; j<100; j++)
				dbShowSprite(j);
			if (gamestate==exitGame)
				break;


			printScoreTime(score);
			i++;
			if (i==10)
			{
				i=0;
				timeS = timeS++;
			}
			dbPrint(timeS);
			dbSetCursor(140, 120); //set cursor for minutes
			if (timeS==60)
			{
				timeS=0;
				j=0;
				timeM=timeM++;
			}
			dbPrint(timeM);


			// user input (arrow keys)-using enum direction 
			if (dbRightKey())
				direction = right;
			if (dbDownKey())
				direction = down;
			if (dbLeftKey())
				direction = left;
			if (dbUpKey())
				direction = up;


			for (int i=1; i<segmentSize; i++)
			{
				previousX[i] = dbSpriteX(i);
				previousY[i] = dbSpriteY(i);
			}



			switch(direction){
				case right:
					x += BLOCK_SIZE;
					break;
				case down:
					y += BLOCK_SIZE;
					break;
				case left:
					x -= BLOCK_SIZE;
					break;
				case up:
					y -= BLOCK_SIZE;
					break;
			}

			dbSprite(1, x, y, 1);



			for (int i=1; i < segmentSize; i++)
			{
				dbSprite(i+1, previousX[i], previousY[i], 1);
			}


			if (dbSpriteHit(1, 101) > 0)// checking collision with normal food
			{		
				int foodType = rand() % 7;		//generating random number to determine whether a powerup or regular food is generated (between 0 and 9)
				int minVal=80;//grace number so food is not generated within wall
				int maxValX = dbScreenWidth() - minVal;
				int maxValY = dbScreenHeight() - minVal;
				int randNumX = rand()%((maxValX-minVal) + 1) + minVal;//int randNum = rand()%(max-min + 1) + min;
				int randNumY = rand()%((maxValY-minVal) + 1) + minVal;
				if (foodType == 3)
				{
					dbSprite(201, randNumX, randNumY, 19);
				}

				else	
				{
					dbSprite(101, randNumX, randNumY, 4);//if foodType isn't our special number (3) then generate a regular food 
					if (scoreIncrement != 20)
						scoreIncrement = 20;
				}



				segmentSize++;
				score = score + scoreIncrement; //increase score because another food was eaten

			}


			if (dbSpriteHit(1, 201) > 0)
			{
				score = score + 50;
				dbDeleteSprite(201);
			}

			//collision with wall (1, 96)
			//collision with segment 
			if( (dbSpriteHit(1,RIGHT_WALL) > 0 || dbSpriteHit(1, LEFT_WALL) > 0 || dbSpriteHit(1, BOTTOM_WALL) || dbSpriteHit(1,TOP_WALL)) && dbSpriteHit(1,0) != 106)//che
			{
				gamestate=menu;
				for (int i=0; i<segmentSize+1; i++)
					dbDeleteSprite(i);//clear screen of segments, you're dead!
				//hide walls(id 96 LEFT_WALL 98 99)
				for (int i=96; i<100; i++)
				{dbDeleteSprite(i);}
				if (screenstate == Large)
					dbText(250, 225, "GAME OVER-You ran into a wall!-Press any key to return to the main menu");


				if (screenstate == Small)
					dbText(50, 150, "GAME OVER-You ran into a wall!-Press any key to return to the main menu");

				if (score > prevScoreVector[0])
					dbText(50, 135, "NEW high score! You broke the broke the previous record for spot number 1!");

				menustate=initialmenu;

				printHiscores(prevScoreVector);
				dbSync();
				dbWaitKey();

			}

			//segment collision
			for (int i=2; i<segmentSize+1; i++){
				if (dbSpriteHit(1, i) > 0)
				{
					gamestate = menu;
					for (int i=0; i<segmentSize+1; i++)
						dbDeleteSprite(i);//clear screen of segments, you're dead!
					//hide walls(id 96 LEFT_WALL 98 99)
					for (int i=96; i<100; i++)
					{dbDeleteSprite(i);}
					if (screenstate == Large)
						dbText(250, 225, "GAME OVER-You ran into a segment!-Press any key to return to the main menu");

					if (screenstate == Small)
						dbText(50, 150, "GAME OVER-You ran into a segment!-Press any key to return to the main menu");

					menustate = initialmenu;

					printHiscores(prevScoreVector);
					dbSync();
					dbWaitKey();
				}
			}


			if (dbEscapeKey() == 1) //looks to see if escape key is pressed, returns one if pressed
			{
				break; //break from the loop and terminate game
			}

			if (dbSpaceKey() == 1)//temporary gamepause 
			{
				dbText(250, 225, "PAUSED-Press any key to continue");
				dbSync(); 
				dbWaitKey();
			}


			dbSync(); //sync the screen.
		}//this while loop will run 60 times per second

		dbDeleteSprite(201);
		if (gamestate==menu){
			ifstream input(HIGHSCORES);

			//***HIGH SCORES 
			//to create high scores, store 3 highest in vector, if a new incoming score
			//is larger, use that value to replace the old one at that index
			//then rewrite the file using the newly added value
			string prevScore;
			double pass;


			for (int i=0; i<3; i++){
				getline(input, prevScore);
				pass = atoi(prevScore.c_str());
				prevScoreVector[i] = pass;
			}
			//for (int i=0; i<prevScoreVector.size(); i++)
			//{
			if (score > prevScoreVector[0])//if bigger than first element
			{
				prevScoreVector[2] = prevScoreVector[1];
				prevScoreVector[1]=prevScoreVector[0];//move everything over because a new bigger score was found
				prevScoreVector[0] = score;
				//break;
			}
			else if (score > prevScoreVector[1])//if bigger than second element
			{
				prevScoreVector[2]=prevScoreVector[1];
				prevScoreVector[1]=score;
			}
			else if (score > prevScoreVector[2])//if bigger than third element
				prevScoreVector[2] = score;


			//}

			ofstream output(HIGHSCORES);
			//open file for writing with truncate option
			for (int i=0; i<prevScoreVector.size(); i++)
			{
				output << prevScoreVector[i] << endl;
			}
		}


	}



	//avoiding memory leaks
	disallocate();


	return;

}