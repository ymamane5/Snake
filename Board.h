#ifndef BOARD
#define BOARD

#include "Point.h"
#include "MySnake.h"

class Board
{
public:
	Board();
	~Board();

	void startGame();
	void updateSnake();
	void generateFood();
	void drawAll();
	void draw();

private:
	MySnake snake;
	char** myBoard;
	int width, height;
	unsigned int score;
	Point food;
};

#endif // !BOARD

