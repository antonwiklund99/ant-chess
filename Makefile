SOURCES=src/main.cpp src/piece.cpp src/board.cpp
HEADERS=include/board.h include/piece.h
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
