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
using std::sort;

#define SEARCH_DEPTH 4

// The side that we are computing the best move for, used in valueOfBoard function
// to decide who to value it for
char currentTurn;

Move minimaxComputeBestMove(const Board& originalBoard) {
  std::cout << "Starting minimax search" << std::endl;
  currentTurn = originalBoard.get_next_move();
  string bestMove;
  float bestScore = -251, score, alfa = -251, beta = 251;
  auto moves = originalBoard.get_legal_moves();
  sort(moves.begin(), moves.end(), [](const Move& a, const Move& b) {
                                     return a.capture > b.capture;
                                   });
  for (auto i : moves) {
    std::cout << "Calculating minimax for move " << i.notation() << std::endl;

    score = minimax(originalBoard, i.notation(), alfa , beta, SEARCH_DEPTH, false);
    alfa = max(alfa, score);
    std::cout << "Score = " << score << std::endl;
    if (score > bestScore) {
      bestScore = score;
      bestMove = i.notation();
    }
  }

  return Move(bestMove, originalBoard.get_next_move());
}

// Minimax function with alfabeta pruning
float minimax(Board b, const string& moveNotation, float alfa, float beta, int depth, bool maximizingPlayer) {
  b.move_piece(moveNotation);

  if (depth == 0 || b.board_is_checkmate() || b.board_is_stalemate()) {
    return valueOfBoard(b);
  }

  // Sort so moves that capture comes first, to get more cutoffs
  auto lg = b.get_legal_moves();
  sort(lg.begin(), lg.end(), [](const Move& a, const Move& b) {
                               return a.capture > b.capture;
                             });
  float value;
  if (maximizingPlayer) {
    value = -251;
    for (auto i : lg) {
      value = max(value, minimax(b, i.notation(), alfa, beta, depth - 1, false));
      alfa = max(alfa, value);
      if (alfa >= beta)
        break;
    }
    return value;
  }
  else {
    value = 251;
    for (auto i : lg) {
      value = min(value, minimax(b, i.notation(), alfa, beta, depth - 1, true));
      beta = min(beta, value);
      if (alfa >= beta)
        break;
    }
    return value;
  }
}

// https://www.chessprogramming.org/Evaluation
// Return value of board from current turns perspective
float valueOfBoard(const Board& b) {
  float prefix = (currentTurn == 'b') ? 1 : -1;
  if (b.board_is_checkmate())
    return (b.get_next_move() == 'b') ? prefix*-250 : prefix*250;

  if (b.board_is_stalemate())
    return 0;

  float value = 0;

  // Material heuristics
  for (auto i : b.get_black_pieces()) {
    value += prefix*pieceValue(i.symbol);
  }
  for (auto i : b.get_white_pieces()) {
    value -= prefix*pieceValue(i.symbol);
  }

  // Mobilty heuristics
  int currentTurnMoves, opponentTurnMoves;
  Board tmpBoard = b;
  currentTurnMoves = b.legal_moves.size();
  tmpBoard.next_move = (b.next_move == 'b') ? 'w' : 'b';
  tmpBoard.parse_legal_moves(tmpBoard.next_move);
  clean_checked_moves(tmpBoard);
  opponentTurnMoves = tmpBoard.legal_moves.size();
  value += (0.1 * (currentTurnMoves - opponentTurnMoves));
  return value;
}
