#include <cstdlib>
#include <ncurses.h>

// global variables
bool gameOver;
const int width = 20, height = 20; // dimentions of the board
int x, y, FruitX, FruitY, score; // snake's head, cords of the fruit, and player score
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN}; 
eDirection dir; 
int TailX[100],  TailY[100]; // snake's tail
int nTail = 0;  // length of the tail 

void Setup()
{
	initscr(); // initialze ncurses 
	clear(); 
	noecho(); 
	cbreak(); 
	curs_set(0); 

	// initalize game varaibles 
	gameOver = false; 
	dir = STOP; 
	x = width / 2; 
	y = height / 2; 
	FruitX = (rand()% width) + 1;
	FruitY = (rand() % height) + 1;
	score = 0;   
}

void Draw()
{
	clear(); 
	// draw borders
	for(int i = 0; i < width + 2; i++)
		mvprintw(0,i,"+"); 
	
	for(int i = 0; i < height + 2; i++)
	{
		for(int j = 0; j < width + 2; j++)
		{
			if(i == 0 || i == 21)
				mvprintw(i,j,"+");

			// draw snake, fruit and tail
			else if(j == 0 || j == 21)
				mvprintw(i,j,"+"); 

			else if(i== y && j == x)
				mvprintw(i,j,"O");
			else if(i == FruitY && j == FruitX)
				mvprintw(i,j,"O");  
			else
				for(int k = 0; k < nTail; k++)
				{
					if(TailX[k] == j && TailY[k] == i)
						mvprintw(i,j,"o"); 
				}	
		}
	}
	// print score
	mvprintw(23,0,"Score %d", score); 

	refresh(); 
}

void Input()
{
	keypad(stdscr, TRUE); // allows prog to know special keys (arrow keys)
	halfdelay(1); 

	int c = getch(); // waits for user to press a key and store ASCII variable

	// movement
	switch(c)
	{
		case KEY_LEFT:
			dir = LEFT; 
			break;

		case KEY_RIGHT:
			dir = RIGHT; 
			break; 

		case KEY_UP:
			dir = UP; 
			break; 

		case KEY_DOWN: 
			dir = DOWN; 
			break; 

		case 113:
			gameOver = true; 
			break; 

	}

}


void Logic()
{
	// updating snake tail
	// updates the positions of the snake's tail based on the previous positions and updates the snake's head position
	int prevX = TailX[0]; 
	int prevY = TailY[0]; 
	int prev2X, prev2Y;
	TailX[0] = x;
	TailY[0] = y; 

	for(int i = 1; i < nTail; i++)
	{
		prev2X = TailX[i]; 
		prev2Y = TailY[i];
		TailX[i] = prevX; 
		TailY[i] = prevY; 
		prevX = prev2X; 
		prevY = prev2Y;  
	} 

	// update direction
	switch(dir)
	{
		case LEFT:
			x--; 
			break; 

		case RIGHT:
			x++;
			break; 

		case UP:
			y--; 
			break; 

		case DOWN: 
			y++;
			break; 

		default:
			break;
	}
	
	// checks for collistion and fruit eaten
	if(x > width || x < 1 || y < 1 || y > height)
		gameOver = true; 

	if(x == FruitX && y == FruitY)
	{
		score++; 
		FruitX = (rand() % width) +1;
		FruitY = (rand() % height) + 1; 
		nTail++; 
	}
	for(int i = 0; i < nTail; i++)
	{
		if(TailX[i] == x && TailY[i] == y)
		{
			gameOver = true; 
		}
	}

}


int main()
{

	Setup(); 
	while(!gameOver)
	{
		Draw();
		Input();
		Logic();
	}

	getch(); 
	endwin(); 

	return 0; 
}

