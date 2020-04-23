#include "MySnake.h"
#include "Point.h"

const int snakeLength = 4;
Point startPos = Point(4, 4);

MySnake::MySnake()
{
	d = direction::_right;
	for (int i = 0; i < 4; i++)
		v.push_back(Point(startPos.getX(), startPos.getY() - i));  
}
