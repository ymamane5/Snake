#include <iostream>
#include <thread>
#include <ncurses.h>
#include <unistd.h>
#include "Board.h"
#include "MySnake.h"

using namespace std;

enum direction keyBuff = _right;  //default
int game_over = 0;
Point lastTail;

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
			if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
				myBoard[i][j] = '#'; // wall
			else
				myBoard[i][j] = ' ';
		}
	}
	//add snake
	for(int i = 0; i < snake.getSize(); i++)
		myBoard[snake.getPos(i).getX()][snake.getPos(i).getY()] = '*';
	
	//add food
	// ...

	score = 0;
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
	/*
	move(height/2, width/2);
	c = getch();
	while(c != 27){
		printw("%d", c);
		refresh();
		move(height/2, width/2);
		c = getch();
	}
	*/

	
	move(0, 0);
/*
	//add snake
	for(int i = 0; i < snake.getSize(); i++)
		myBoard[snake.getPos(i).getX()][snake.getPos(i).getY()] = '*';
*/
	//draw
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			printw("%c", myBoard[i][j]);
		}
		//printw("\n");
	}
	refresh();
	//getch();
	
}

void Board::updateSnake()
{
	char c;

	//check head
	if(myBoard[snake.getHead().getX()][snake.getHead().getY()] != ' ')
	{
		//printf("head pos got to: %c\n", myBoard[snake.getHead().getX()][snake.getHead().getY()]);
		game_over = 1;
	}

	for(int i = 0; i < snake.getSize(); i++)
	{
		myBoard[snake.getPos(i).getX()][snake.getPos(i).getY()] = '*';
		move(snake.getPos(i).getX(), snake.getPos(i).getY());
		printw("*");
	}
	move(lastTail.getX(), lastTail.getY());
	printw(" ");
	myBoard[lastTail.getX()][lastTail.getY()] = ' ';
	c = wgetch(stdscr);
	//move(height, 0);
	//printw("%c",c);
	refresh();
}

void Board::draw()
{
		
}

void checkKeyPress()
{
	//cout << "inside checkKeyPress" << endl;
	nodelay(stdscr, TRUE);
	char c;

	while (keyBuff != exitGame)
	{
		c = getch();

		if (c == 27)
			keyBuff = exitGame;
		else if (c == 'a' && keyBuff != _right)
				keyBuff = _left;
		else if (c == 'd' && keyBuff != _left)
			keyBuff = _right;
		else if (c == 'w' && keyBuff != _down)
			keyBuff = _up;
		else if (c == 's' && keyBuff != _up)
			keyBuff = _down;
	}
	
}

void Board::startGame()
{
	drawAll();

	thread keyboard(checkKeyPress);
	keyboard.detach();

	while(keyBuff != exitGame && game_over == 0)  
	{
		lastTail = snake.getTail();

		if (keyBuff == _up)
			snake.goUp();
		else if (keyBuff == _down)
			snake.goDown();
		else if (keyBuff == _right)
			snake.goRight();
		else if (keyBuff == _left)
			snake.goLeft();
			
		updateSnake();
		// generateFood();
		usleep(100000);
	}

	if(game_over == 1)
	{
		move(height/2, width/2 - 5);
		printw("Game Over!");
		sleep(2);
	}
	
	endwin();
}
