out: Main.o Board.o MySnake.o
	g++ Main.o Board.o MySnake.o -lncurses -lpthread -o out 
Main.o: Main.cpp
	g++ -c Main.cpp
Board.o: Board.cpp Board.h Point.h
	g++ -c Board.cpp
MySnake.o: MySnake.cpp MySnake.h Point.h
	g++ -c MySnake.cpp