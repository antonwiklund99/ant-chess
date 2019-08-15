#ifndef POSITION_GUARD
#define POSITION_GUARD

#include "board.h"
#include "piece.h"

struct Position {
  Board board;
  Color turn;
  bool wcastling;
  bool bcastling;
  unsigned int halfMoveClock;

  Position():turn(cWhite), wcastling(true), bcastling(true), halfMoveClock(0) {}
};

#endif
