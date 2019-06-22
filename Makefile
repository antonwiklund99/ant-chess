CC=g++
CPPFLAGS=-Wall -g -Iinclude

game : board.o main.o piece.o move.o
	$(CC) $(CPPFLAGS) -o game board.o main.o piece.o move.o
main.o : include/board.h include/piece.h include/move.h src/main.cpp src/board.cpp src/piece.cpp
	$(CC) $(CPPFLAGS) -g -c src/main.cpp
board.o : include/board.h include/piece.h include/move.h src/board.cpp src/piece.cpp
	$(CC) $(CPPFLAGS) -c src/board.cpp src/move.cpp src/piece.cpp
piece.o: include/piece.h src/piece.cpp
	$(CC) $(CPPFLAGS) -c src/piece.cpp
move.o: include/move.h src/move.cpp
	$(CC) $(CPPFLAGS) -c src/move.cpp
clean :
				rm game main.o board.o piece.o move.o
