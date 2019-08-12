#ifndef MINIMAX_GUARD
#define MINIMAX_GUARD

#include <vector>
#include <string>
#include "board.h"
#include "move.h"

Move minimaxComputeBestMove(const Board&);
float minimax(Board, const std::string&, float, float, int, bool);
float valueOfBoard(const Board&);
#endif
