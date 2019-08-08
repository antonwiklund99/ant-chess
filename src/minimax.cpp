#include <stdexcept>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include "minimax.h"
#include "move.h"
#include "board.h"
using std::string;
using std::max;
using std::min;

#define SEARCH_DEPTH 2

Move minimaxComputeBestMove(const Board& originalBoard) {
  std::cout << "Starting minimax search" << std::endl;
  string bestMove;
  int bestScore = -201, score;
  for (auto i : originalBoard.get_legal_moves()) {
    std::cout << "Calculating minimax for move " << i.notation() << std::endl;

    score = minimax(originalBoard, i.notation(), SEARCH_DEPTH, false);

    std::cout << "Score = " << score << std::endl;
    if (score > bestScore) {
      bestScore = score;
      bestMove = i.notation();
    }
  }

  return Move(bestMove, originalBoard.get_next_move());
}

int minimax(Board b, const string& moveNotation, int depth, bool maximizingPlayer) {
  b.move_piece(moveNotation);

  if (depth == 0 || b.board_is_checkmate() || b.board_is_stalemate()) {
    return valueOfBoard(b);
  }

  int value;
  if (maximizingPlayer) {
    value = -201;
    for (auto i : b.get_legal_moves()) {
      value = max(value, minimax(b, i.notation(), depth - 1, false));
    }
    return value;
  }
  else {
    value = 201;
    for (auto i : b.get_legal_moves()) {
      value = min(value, minimax(b, i.notation(), depth - 1, true));
    }
    return value;
  }
}

// https://www.chessprogramming.org/Evaluation
// Return value of board from whites perspective (TODO MAKE IT INDEPENDENT)
int valueOfBoard(const Board& b) {
  if (b.board_is_checkmate())
    return (b.get_next_move() == 'b') ? 200 : -200;

  if (b.board_is_stalemate())
    return 0;

  int value = 0;
  // Material heuristics
  for (auto i : b.get_black_pieces()) {
    value -= pieceValue(i.symbol);
  }
  for (auto i : b.get_white_pieces()) {
    value += pieceValue(i.symbol);
  }

  return value;
}
