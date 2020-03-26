#ifndef MINIMAX_GUARD
#define MINIMAX_GUARD

#include "position.h"

Move minimaxComputeBestMove(Position);
float minimax(Position&, float, float, int, bool);
float valueOfPos(const Position&);
#endif
