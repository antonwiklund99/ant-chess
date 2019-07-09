SOURCES=$(wildcard src/*.cpp)
HEADERS=include/board.h include/piece.h include/move.h
OBJECTS=$(patsubst src/%.cpp, src/%.o, $(SOURCES))

CC=g++
CPPFLAGS=-Wall -g -Iinclude

main: $(OBJECTS)
	$(CC) $(CPPFLAGS) $(OBJECTS) -o main
$(OBJECTS): src/%.o : src/%.cpp $(HEADERS)
	$(CC) $(CPPFLAGS) -c $< -o $@
clean:
	rm -f src/*.o main
