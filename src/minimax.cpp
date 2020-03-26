#include <stdexcept>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include "minimax.h"
#include "move.h"
#include "enums.h"
#include "utils.h"
using std::max; using std::min;
using std::sort; using std::vector;

#define SEARCH_DEPTH 10

// The side that we are computing the best move for, used in valueOfPos function
// to decide who to value it for
Color currentTurn;

Move minimaxComputeBestMove(Position original) {
  std::cout << "Starting minimax search" << std::endl;
  Move* bestMove = nullptr;
  float bestScore = -251, score, alfa = -251, beta = 251;
  vector<Move> moves;
  currentTurn = original.turn;
  generateMoves(original, moves, original.turn);
  sort(moves.begin(), moves.end(), [](const Move& a, const Move& b) {
                                     return a.isCapture() > b.isCapture();
                                   });
  for (int i = 0; i < moves.size(); i++) {
    Move* m = &moves[i];
    std::cout << "Calculating minimax for move " << m->notation();
    original.makeMove(*m);
    score = minimax(original, alfa , beta, SEARCH_DEPTH, false);
    alfa = max(alfa, score);
    std::cout << ", score = " << score << std::endl;
    if (score > bestScore) {
      bestScore = score;
      bestMove = &moves[i];
    }
    original.unmakeMove(*m);
  }

  return *bestMove;
}

// Minimax function with alfabeta pruning
float minimax(Position& pos, float alfa, float beta, int depth, bool maximizingPlayer) {
  //std::cout << "DEPTH = " << depth << " MAXIMIZING = " << maximizingPlayer << std::endl;
  if (depth == 0) {
    return valueOfPos(pos);
  }

  // Sort so moves that capture comes first, to get more cutoffs
  vector<Move> lg;
  generateMoves(pos, lg);
  sort(lg.begin(), lg.end(), [](const Move& a, const Move& b) {
                               return a.isCapture() > b.isCapture();
                             });
  float value;
  bool checkmate = true;
  if (maximizingPlayer) {
    value = -251;
    for (auto m : lg) {
      if (pos.makeMove(m)) {
        checkmate = false;
        value = max(value, minimax(pos, alfa, beta, depth - 1, false));
        alfa = max(alfa, value);
        if (alfa >= beta)
          break;
        /* Kanske skulle vara bättre att skicka med move som argument och göra makeMove i början
         av funktionen och undvika den här unmake:n. Jobbiga med det var att ta reda på
         checkmate/stalemate då eftersom generateMoves genererar pseudo legal moves, nivån
         ovanför skulle inte veta att move:t inte var legit*/
        pos.unmakeMove(m);
      }
    }
  }
  else {
    value = 251;
    for (auto m : lg) {
      if (pos.makeMove(m)) {
        checkmate = false;
        value = min(value, minimax(pos, alfa, beta, depth - 1, true));
        beta = min(beta, value);
        if (alfa >= beta)
          break;
        pos.unmakeMove(m);
      }
    }
  }
  // väldigt fult
  if (checkmate) {
    if (pos.board.isAttacked(pos.turn == cWhite ? pos.board.getWhiteKing() :
                             pos.board.getBlackKing(), pos.turn == cWhite ? cBlack : cWhite))
      return 250*(maximizingPlayer ? -1 : 1);
    else
      return 0;
  }
  else return value;
}

// https://www.chessprogramming.org/Evaluation
// Return value of position from current turns perspective
float valueOfPos(const Position& pos) {
  float value =
    9*(countOnes(pos.board.getWhiteQueen()) - countOnes(pos.board.getBlackQueen())) +
    5*(countOnes(pos.board.getWhiteRooks()) - countOnes(pos.board.getBlackRooks())) +
    3*(
       countOnes(pos.board.getWhiteKnights()) - countOnes(pos.board.getBlackKnights()) +
       countOnes(pos.board.getWhiteBishops()) - countOnes(pos.board.getBlackBishops())
       ) +
    (countOnes(pos.board.getWhitePawns() - pos.board.getBlackPawns()))
    // TODO: 0,5*(doubled, blocked and isolated pawns)
    ;

  // Mobilty heuristics
  vector<Move> whiteMoves, blackMoves;
  generateMoves(pos, whiteMoves, cWhite);
  generateMoves(pos, blackMoves, cBlack);
  value += 0.5*(whiteMoves.size() - blackMoves.size());
  return value*(currentTurn == cWhite ? 1 : -1);
}
