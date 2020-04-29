#include <iostream>
#include <thread>
#include <ncurses.h>
#include <unistd.h>
#include <cstdlib>  // for srand
#include "Board.h"
#include "MySnake.h"

using namespace std;

enum direction keyBuff = _right;  //default
int game_over = 0;

Board::Board()
{
	initscr();
	noecho();
	getmaxyx(stdscr, height, width);

	myBoard = new char*[height];
	for(int i = 0; i < height; i++)
		myBoard[i] = new char[width];

	//add wall
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (i == 1 || i == height - 1 || j == 0 || j == width - 1)
				myBoard[i][j] = '#'; // wall
			else
				myBoard[i][j] = ' ';
		}
	}
	myBoard[0][width - 1] = ' ';
	//add snake
	for(int i = 0; i < snake.getSize(); i++)
		myBoard[snake.getPos(i).getX()][snake.getPos(i).getY()] = '*';
	
	//add food
	// ...

	score = 0;
	incSnake = 0;
}

Board::~Board()
{
	for(int i = 0; i < height; i++)
		delete(myBoard[i]);

	delete myBoard;
}

void Board::drawAll()
{	
	char c;
	move(0, 0);

	//draw board
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			printw("%c", myBoard[i][j]);
		}
	}

	refresh();
}

void Board::updateSnake()
{
	//check head
	if(myBoard[snake.getHead().getX()][snake.getHead().getY()] != ' ')
	{
		if(myBoard[snake.getHead().getX()][snake.getHead().getY()] == '$'){
			incSnake += 2;
			score += 10;
			generateFood();
		}
		else {
			game_over = 1;
			//printf("head pos got to: %c\n", myBoard[snake.getHead().getX()][snake.getHead().getY()]);
		}
	}
	// print snake
	for(int i = 0; i < snake.getSize(); i++)
	{
		myBoard[snake.getPos(i).getX()][snake.getPos(i).getY()] = '*';
		move(snake.getPos(i).getX(), snake.getPos(i).getY());
		printw("*");
	}
	move(lastTail.getX(), lastTail.getY());
	printw(" ");
	myBoard[lastTail.getX()][lastTail.getY()] = ' ';
	//c = wgetch(stdscr);
	refresh();
}

void getKeyPress(MySnake* snake)
{
	//cout << "inside checkKeyPress" << endl;
	nodelay(stdscr, TRUE);
	char c;

	while (keyBuff != exitGame)
	{
		c = getch();

		if (c == 27)
			keyBuff = exitGame;
		else if (c == 'a' && snake->getDir() != _right)
				keyBuff = _left;
		else if (c == 'd' && snake->getDir() != _left)
			keyBuff = _right;
		else if (c == 'w' && snake->getDir() != _down)
			keyBuff = _up;
		else if (c == 's' && snake->getDir() != _up)
			keyBuff = _down;
	}
	
}

void Board::startGame()
{
	drawAll();
	getch();
	generateFood();

	thread keyboard(getKeyPress, &snake);
	keyboard.detach();

	while(keyBuff != exitGame && game_over == 0)  
	{
		lastTail = snake.getTail();

		if (keyBuff == _up){
			snake.goUp(incSnake); snake.setDir(_up);
		}
		else if (keyBuff == _down){
			snake.goDown(incSnake); snake.setDir(_down);
		}
		else if (keyBuff == _right){
			snake.goRight(incSnake); snake.setDir(_right);
		}
		else if (keyBuff == _left){
			snake.goLeft(incSnake); snake.setDir(_left);
		}

		updateSnake();
		move(0,0);
		printw("score: %d", score);
		refresh();

		if(incSnake > 0)
			incSnake--;

		usleep(100000);
	}

	if(game_over == 1)
	{
		gameOver();
	}
	
	endwin();
}

void Board::generateFood()
{
	int row, col;

	do {
	row = (rand() % (height - 3)) + 2;
	col = (rand() % (width - 2)) + 1;
	} while(!foodIsOk(row, col));

	myBoard[row][col] = '$';
	move(row, col);
	printw("$");
	refresh();
}

bool Board::foodIsOk(int row, int col)
{
	for(int i = 0; i < snake.getSize(); i++)
		if(row = snake.getPos(i).getX() && col == snake.getPos(i).getY())
			return false;

	return true;
}

void Board::gameOver()
{
	move(height/2, width/2 - 5);
	printw("Game Over!  ");
	sleep(2);
}
