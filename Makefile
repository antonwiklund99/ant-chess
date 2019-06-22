CC=g++
CPPFLAGS=-Wall -g -Iinclude

game : board.o main.o piece.o
	$(CC) $(CPPFLAGS) -o game board.o main.o piece.o
main.o : include/board.h include/piece.h src/main.cpp src/board.cpp src/piece.cpp
	$(CC) $(CPPFLAGS) -g -c src/main.cpp
board.o : include/board.h include/piece.h src/board.cpp src/piece.cpp
	$(CC) $(CPPFLAGS) -c src/board.cpp
piece.o: include/piece.h src/piece.cpp
	$(CC) $(CPPFLAGS) -c src/piece.cpp
clean :
				rm game main.o board.o piece.o
