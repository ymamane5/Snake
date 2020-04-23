#ifndef SNAKE
#define SNAKE

#include<vector>
#include "Point.h"

enum direction{ _left, _right, _up, _down, exitGame };

class MySnake
{
public:
	MySnake();
	~MySnake() {}

	Point getHead() { return v.front(); }
	Point getTail() { return v.back(); }
	Point getPos(int i) { return v.at(i); }
	direction getDir() { return d; }
	void setDir(enum direction direction) { d = direction; }

	void goUp();
	void goDown();
	void goRight();
	void goleft();
	
private:
	vector<Point> v;
	direction d;
	//unsigned int length;
};

#endif // !SNAKE