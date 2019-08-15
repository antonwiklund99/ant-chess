SOURCES=src/main.cpp src/piece.cpp src/board.cpp src/position.cpp src/move.cpp
HEADERS=include/board.h include/piece.h include/position.h include/move.h
OBJECTS=$(patsubst src/%.cpp, src/%.o, $(SOURCES))

CC=g++
CPPFLAGS=-Wall -g -O2 -Iinclude
LIBS=-lSDL2

main: $(OBJECTS)
	$(CC) $(CPPFLAGS) $(OBJECTS) $(LIBS) -o main
$(OBJECTS): src/%.o : src/%.cpp $(HEADERS)
	$(CC) $(CPPFLAGS) -c $< -o $@
clean:
	rm -f src/*.o main
