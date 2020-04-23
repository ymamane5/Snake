#include<iostream>
#include<windows.h>
#include<thread>
#include "Board.h"

// test

using namespace std;

enum direction keyBuff = _right;
Point Board::snakeStart = Point(4, 4);

Board::Board()
{
	for (int i = 0; i <= ROWS + 1; i++)
	{
		for (int j = 0; j <= COL + 1; j++)
		{
			if (i == 0 || i == ROWS + 1 || j == 0 || j == COL + 1)
				myBoard[i][j] = '#'; // wall
			else if (i == snakeStart.getX() && j <= snakeStart.getY() && j >= 1)
				myBoard[i][j] = '*'; // snake
			else
				myBoard[i][j] = ' ';
		}
	}
	
	score = 0;
}

void Board::draw()
{	
	//add snake
	for(int i = 0; i < 4; i++)
		myBoard[snake.getPos(i).getX()][snake.getPos(i).getY()] = '*';
	
	for (int i = 0; i <= ROWS + 1; i++)
	{
		for (int j = 0; j <= COL + 1; j++)
		{
			cout << myBoard[i][j];
		}
		cout << endl;
	}
}

void checkKeyPress()
{
	//cout << "inside checkKeyPress" << endl;

	while (keyBuff != exitGame)
	{
		if (GetKeyState(VK_ESCAPE) & 0x8000)
			keyBuff = exitGame;
		else if (GetKeyState(VK_LEFT) & 0x8000)
			keyBuff = _left;
		else if (GetKeyState(VK_RIGHT) & 0x8000)
			keyBuff = _right;
		else if (GetKeyState(VK_UP) & 0x8000)
			keyBuff = _up;
		else if (GetKeyState(VK_DOWN) & 0x8000)
			keyBuff = _down;
	}
}
/*
void Board::goUp()
{
	cout << "inside goUp" << endl;
	myBoard[snake.getTail().getX()][snake.getTail().getY()] = ' ';
	myBoard[snake.getHead().getX() - 1][snake.getHead().getY()] = '*';
	draw();

	snake.setDir(_up);
}
*/

void Board::startGame()
{
	//int i = 0;
	thread keyboard(checkKeyPress);
	keyboard.detach();

	while(keyBuff != exitGame)  
	{
		//cout << "keybuff = " << keyBuff << endl;
		//if (keyBuff == _UP)
			//snake.goUp();
			
		Sleep(1000);
	}
}
