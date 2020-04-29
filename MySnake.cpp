#include "MySnake.h"
#include "Point.h"

//const int snakeLength = 4;
//Point startPos = Point(4, 4);

const Point MySnake::startHead = Point(START_ROW, START_LENGTH);
const Point MySnake::startTail = Point(START_ROW,1);

MySnake::MySnake()
{
	d = direction::_right;
	for (int i = 0; i < START_LENGTH; i++)
		v.push_back(Point(START_ROW, START_LENGTH - i));  
}

MySnake::MySnake(int start_length)
{
	d = direction::_right;
	for (int i = 0; i < start_length; i++)
		v.push_back(Point(START_ROW, start_length - i));
}

void MySnake::goUp(int inc)
{
	Point newHead = Point(v.front().getX() - 1, v.front().getY());

	if(inc == 0)
		v.pop_back(); // delete tail
	
	v.emplace(v.begin(), newHead); // new head
}

void MySnake::goDown(int inc)
{
	Point newHead = Point(v.front().getX() + 1, v.front().getY());

	if(inc == 0)
		v.pop_back(); // delete tail

	v.emplace(v.begin(), newHead); // new head
}

void MySnake::goRight(int inc)
{
	Point newHead = Point(v.front().getX(), v.front().getY() + 1);

	if(inc == 0)
		v.pop_back(); // delete tail
	
	v.emplace(v.begin(), newHead); // new head
}

void MySnake::goLeft(int inc)
{
	Point newHead = Point(v.front().getX(), v.front().getY() - 1);

	if(inc == 0)
		v.pop_back(); // delete tail
	
	v.emplace(v.begin(), newHead); // new head	
}