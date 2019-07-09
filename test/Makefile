TESTCASES=$(wildcard *.cpp)
SOURCES=$(wildcard ../src/*.cpp)
HEADERS=../include/board.h ../include/move.h ../include/piece.h
OBJECTS=$(patsubst %.cpp, %.o, $(TESTCASES))

CC=g++
CPPFLAGS=-Wall -g -I../include

test: board_test.o move_test.o piece_test.o
	$(CC) $(CPPFLAGS) board_test.o move_test.o piece_test.o -lboost_unit_test_framework -o test
board_test.o: $(HEADERS) board_test.cpp $(SOURCES)
	$(CC) $(CPPFLAGS) -c board_test.cpp $(SOURCES) -lboost_unit_test_framework
piece_test.o: $(HEADERS) piece_test.cpp $(SOURCES)
	$(CC) $(CPPFLAGS) -c piece_test.cpp $(SOURCES) -lboost_unit_test_framework
move_test.o: $(HEADERS) move_test.cpp $(SOURCES)
	$(CC) $(CPPFLAGS) -c move_test.cpp $(SOURCES) -lboost_unit_test_framework
clean:
	rm -f test *.o
