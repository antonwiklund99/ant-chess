SOURCES=../src/piecePatterns.cpp ../src/piece.cpp ../src/board.cpp ../src/position.cpp ../src/move.cpp ../src/magic.cpp boardTest.cpp
HEADERS=../include/piecePatterns.h ../include/board.h ../include/piece.h ../include/position.h ../include/move.h ../include/magic.h
OBJECTS=$(patsubst %.cpp, %.o, $(SOURCES))

CC=g++
CPPFLAGS=-Wall -g -I../include
LIBS=-lboost_unit_test_framework

test: boardTest.o
	$(CC) $(CPPFLAGS) $(OBJECTS) $(LIBS) -o test
$(OBJECTS): %.o : %.cpp $(HEADERS)
	$(CC) $(CPPFLAGS) -c $< -o $@
clean:
	rm -f test *.o
