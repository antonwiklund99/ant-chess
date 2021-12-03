SOURCES=src/utils.cpp src/main.cpp src/bitboards.cpp src/board.cpp src/book.cpp src/position.cpp src/move.cpp src/minimax.cpp src/benchmarks.cpp src/uci.cpp
HEADERS=include/utils.h include/bitboards.h include/book.h include/board.h include/position.h include/move.h include/enums.h include/minimax.h include/uci.h
OBJECTS=$(patsubst src/%.cpp, src/%.o, $(SOURCES))
BENCH_OBJECTS=$(filter-out src/main.o, $(OBJECTS))
MAIN_OBJECTS=$(filter-out src/benchmarks.o, $(OBJECTS))

CC=g++
CPPFLAGS=-Wall -g -O3 -Iinclude
LIBS=-lpthread

main: $(OBJECTS)
	$(CC) $(CPPFLAGS) $(MAIN_OBJECTS) $(LIBS) -o main
benchmarks: $(OBJECTS)
	$(CC) $(CPPFLAGS) $(BENCH_OBJECTS) $(LIBS) -o benchmarks
$(OBJECTS): src/%.o : src/%.cpp $(HEADERS)
	$(CC) $(CPPFLAGS) -c $< -o $@
clean:
	rm -f src/*.o main benchmarks test/*.o test/test log.txt
