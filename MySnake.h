#ifndef SNAKE
#define SNAKE

#include<vector>
#include "Point.h"

#define START_ROW 10
#define START_LENGTH 4

enum direction { _left, _right, _up, _down, exitGame };

class MySnake
{
public:
	static const Point startHead;
	static const Point startTail;

	MySnake();
	MySnake(int start_length);
	~MySnake() {}

	Point getHead() { return v.front(); }
	Point getTail() { return v.back(); }
	Point getPos(int i) { return v.at(i); }
	direction getDir() { return d; }
	void setDir(enum direction direction) { d = direction; }
	unsigned int getSize() { return v.size(); }

	void goUp(int);
	void goDown(int);
	void goRight(int);
	void goLeft(int);
	
private:
	vector<Point> v;
	direction d;
};

#endif // !SNAKE