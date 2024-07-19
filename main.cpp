/* Justin Isaraphanich
Snake Game in the terminal
6/25/2024 */

#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;

//initialize global variables
bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100], nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup()
{
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}

void Draw()
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
	for (int i = 0; i < width + 2; i++)
	{
		cout << "#";
	}
	cout << endl;
	
	//create the border of the game
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if(j == 0) {
				cout << "#";
			}
			if (i == y && j == x) {
				cout << "O";
			}
			else if (i == fruitY && j == fruitX) {
				cout << "F";
			}
			else {
				//this segment prints the tail
				bool print = false;
				for (int k = 0; k < nTail; k++) {
					
					if (tailX[k] == j && tailY[k] == i) {
						cout << "o";
						print = true;
					}					
				}
				if (!print) {
					cout << " ";
				}
			}
			
			
			if(j == width - 1) {
				cout << "#";
			}
		}
		cout << endl;
	}
	
	for(int i = 0; i < width + 2; i++)
	{
		cout << "#";
	}
	cout << endl;
	//display the score below the border of the game
	cout << "Score: " << score << endl;
}

void Input()
{
	//create the logic and input for the head of the snake to move
	//i.e write down the functions to allow user to move snake
	if (_kbhit()) {
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}

void Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;

	//function to move the tail
	for(int i = 1; i < nTail; i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		//remember position at current 2 values above
		tailX[i] = prevX;
		tailY[i] = prevY;
		//update prevX and prevY to prev2N
		prevX = prev2X;
		prevY = prev2Y;
	}
	
	//logic to actually get the snake to move. 
	//previous switch was getting system to recognize the inputs and differentiate
	switch (dir)
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
	//code that ends the game if the snake hits the wall
	if (x > width || x < 0 || y > height || y < 0) {
		gameOver = true;
	}
	//optional code to not let the walls = gameover, instead you wrap around the border:
	/* if(x >= width) x = 0; else if (x < 0) x = width - 1;
	if(y >= height) y = 0; else if (y < 0) y = height - 1;*/

	//create code that ends game if you hit your tail
	for (int i = 0; i < nTail; i++) {
		if (tailX[i] == x && tailY[i] == y) {
			gameOver = true;
		}
	}
	//statement that moves the fruit to a different random position when it is 'eaten'
	if (x == fruitX && y == fruitY) {
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
}


int main(int argc, const char* argv[]) {
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(45);
	}

	return 0;
}