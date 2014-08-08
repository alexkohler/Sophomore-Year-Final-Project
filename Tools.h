//Tools- misc funtions for snake
//Written by Alexander Kohler

#include <vector>
using namespace std;

void printHiscores (const vector<double> prevScoreVector)
{
				dbText(50, 175, "Previous High Scores:");//Printing High Scores
				dbSetCursor(50, 200);
				dbPrint(prevScoreVector[0]);
				dbSetCursor(50, 225);
				dbPrint(prevScoreVector[1]);
				dbSetCursor(50, 250);
				dbPrint(prevScoreVector[2]);
}

//to avoid memory leaks 
void disallocate()
{
	for (int i = 1; i < 10; i++)
	{
		dbDeleteImage(i);
		dbDeleteSprite(i); 
	}

}



