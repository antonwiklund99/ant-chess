#ifndef POSITION_GUARD
#define POSITION_GUARD

#include "board.h"
#include "move.h"
#include "enums.h"
#include <vector>
#include <stack>

class Info {
public:
	Info(unsigned int x): encodedInfo(x) {}
	bool getWKingCastling()  { return encodedInfo & 1; };
	bool getWQueenCastling() { return encodedInfo & 2; };
	bool getBKingCastling()  { return encodedInfo & 4; };
	bool getBQueenCastling() { return encodedInfo & 8; };
	unsigned int getHalfMoveClock() { return encodedInfo >> 4; };
private:
	// bit 1 - wKingsidecastling
	// bit 2 - wQueensidecastling
	// bit 3 - bKingsidecastling
	// bit 4 - bQueensidecastling
	// bit 5-32 - halfmoveclock (max 50 so will only ever use 6 bits)
	unsigned int encodedInfo;
};

class Position {
 public:
  Board board;
  Color turn;
	std::stack<Info*> states;
  bool wKingsideCastling;
	bool wQueensideCastling;
	bool bKingsideCastling;
	bool bQueensideCastling;
  unsigned int halfMoveClock;
	unsigned int fullMoveNumber;
	Position(std::string);
	Position():turn(cWhite), wKingsideCastling(true), wQueensideCastling(true),
						 bKingsideCastling(true), bQueensideCastling(true), halfMoveClock(0), fullMoveNumber(1)
	{}

  bool makeMove(const Move&);
  void unmakeMove(const Move&);
	Info* getInfo();
};

void generateMoves(const Position&, std::vector<Move>&, Color);
void generateMoves(const Position&, std::vector<Move>&);
std::vector<Move> legalMoves(Position&);
Bitboard perft(int, Position&);
#endif
