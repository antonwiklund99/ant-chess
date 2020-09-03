#ifndef MINIMAX_GUARD
#define MINIMAX_GUARD

#include "position.h"

Move minimaxComputeBestMove(Position, int, bool);
Move minimaxComputeBestMove(Position, int);
float minimax(Position &, float, float, int, bool);
float valueOfPos(const Position &);
#endif
