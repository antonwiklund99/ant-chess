#ifndef POSITION_GUARD
#define POSITION_GUARD

#include "board.h"
#include "move.h"
#include "enums.h"

class Position {
 public:
  Board board;
  Color turn;
  bool wcastling;
  bool bcastling;
  unsigned int halfMoveClock;
	unsigned int fullMoveNumber;
	Position(std::string);
	Position():turn(cWhite), wcastling(true), bcastling(true), halfMoveClock(0), fullMoveNumber(1) {}
	Position(Board b, Color t, bool wc, bool bc, unsigned int hmc, unsigned int fmn):
		board(b), turn(t), wcastling(wc), bcastling(bc), halfMoveClock(hmc), fullMoveNumber(fmn) {}

  bool makeMove(const Move&);
  void unmakeMove(const Move&);
};

void generateMoves(const Position&, std::vector<Move>&, Color);
void generateMoves(const Position&, std::vector<Move>&);
std::vector<Move> legalMoves(Position&);
#endif
