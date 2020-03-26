SOURCES=src/utils.cpp src/main.cpp src/piecePatterns.cpp src/board.cpp src/position.cpp src/move.cpp src/magic.cpp src/minimax.cpp
HEADERS=include/utils.h include/piecePatterns.h include/board.h include/position.h include/move.h include/magic.h include/enums.h include/minimax.h
OBJECTS=$(patsubst src/%.cpp, src/%.o, $(SOURCES))

CC=g++
CPPFLAGS=-Wall -g -O2 -Iinclude
LIBS=-lSDL2

main: $(OBJECTS)
	$(CC) $(CPPFLAGS) $(OBJECTS) $(LIBS) -o main
$(OBJECTS): src/%.o : src/%.cpp $(HEADERS)
	$(CC) $(CPPFLAGS) -c $< -o $@
clean:
	rm -f src/*.o main test/*.o test/test
