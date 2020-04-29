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
	void gameOver();
	bool foodIsOk(int row, int col);
	unsigned int getScore() { return score; }
	void incScore() { score += 10; }

	//void getKeyPress();

private:
	MySnake snake;
	char** myBoard;
	int width, height;
	unsigned int score;
	Point food;
	Point lastTail;
	int incSnake;
};

#endif // !BOARD

