#ifndef POINT
#define POINT

#include <iostream>

using namespace std;

class Point {
public:
	Point() { this->x = 0; this->y = 0; }
	Point(int x, int y) { this->x = x; this->y = y; }
	//Point(Point& p) { this->x = p.getX(); this->y = p.getY(); }
	~Point() {};

	void setX(int x) { this->x = x; }
	int getX() { return x; }
	void setY(int y) { this->y = y; }
	int getY() { return y; }
	void print() { cout << "(" << x << "," << y << ")\n"; }
	/*
	void decX() { x--; }
	void incX() { x++; }
	void decY() { y--; }
	void incY() { y++; }
	*/

private:
	int x;
	int y;
};

#endif // !POINT

