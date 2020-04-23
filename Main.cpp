#include <iostream>
#include<thread>
#include "MySnake.h"
#include "Board.h"
#include "Point.h"

using namespace std;

int main() 
{
	Board board;

	board.draw();
	board.startGame();
	system("pause");

	return 0;
}