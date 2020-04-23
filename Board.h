#ifndef BOARD
#define BOARD

#include "Point.h"
#include "MySnake.h"

int const ROWS = 10, COL = 10;

class Board
{
public:
	Board();  // 1 - wall;  2 - snake;  3 - food;
	~Board() {}

	void startGame();
	void generateFood();
	void draw();

private:
	char myBoard[ROWS + 2][COL + 2];
	MySnake snake;
	static Point snakeStart;
	unsigned int score;
	Point food;
};

#endif // !BOARD

