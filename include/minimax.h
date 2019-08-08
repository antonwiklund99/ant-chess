#ifndef MINIMAX_GUARD
#define MINIMAX_GUARD

#include <vector>
#include <string>
#include "board.h"
#include "move.h"

Move minimaxComputeBestMove(const Board&);
int minimax(Board, const std::string&, int, bool);
int valueOfBoard(const Board&);
#endif
