#include "minimax.h"
#include "enums.h"
#include "move.h"
#include "utils.h"
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
using std::max;
using std::min;
using std::sort;
using std::vector;

// The side that we are computing the best move for, used in valueOfPos function
// to decide who to value it for
Color currentTurn;

Move minimaxComputeBestMove(Position original, int depth, bool info) {
  int bestMove = 0;
  float bestScore = -251, score, alfa = -251, beta = 251;
  vector<Move> moves = legalMoves(original);
  currentTurn = original.turn;
  sort(moves.begin(), moves.end(), [](const Move &a, const Move &b) {
    return a.isCapture() > b.isCapture();
  });
  for (size_t i = 0; i < moves.size(); i++) {
    Move m = moves[i];
    if (info)
      std::cout << "info currmove " << m.notation() << " currmovenumber "
                << i + 1 << std::endl;
    original.makeMove(m);
    score = minimax(original, alfa, beta, depth, false);

    alfa = max(alfa, score);
    if (score > bestScore) {
      bestScore = score;
      bestMove = i;
    }
    original.unmakeMove(m);
  }
  if (info)
    std::cout << "info score cp " << ((int)bestScore) << " pv "
              << moves[bestMove].notation() << std::endl;
  return moves[bestMove];
}

Move minimaxComputeBestMove(Position p, int d) {
  return minimaxComputeBestMove(p, d, true);
}

// Minimax function with alfabeta pruning
float minimax(Position &pos, float alfa, float beta, int depth,
              bool maximizingPlayer) {
  // std::cout << "DEPTH = " << depth << " MAXIMIZING = " << maximizingPlayer <<
  // std::endl;
  if (depth == 0) {
    return valueOfPos(pos);
  }

  // Sort so moves that capture comes first, to get more cutoffs
  vector<Move> lg;
  generateMoves(pos, lg);
  sort(lg.begin(), lg.end(), [](const Move &a, const Move &b) {
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
        pos.unmakeMove(m);
        if (alfa >= beta)
          break;
        /* Kanske skulle vara bättre att skicka med move som argument och göra
         makeMove i början av funktionen och undvika den här unmake:n. Jobbiga
         med det var att ta reda på checkmate/stalemate då eftersom
         generateMoves genererar pseudo legal moves, nivån ovanför skulle inte
         veta att move:t inte var legit*/
      }
    }
  } else {
    value = 251;
    for (auto m : lg) {
      if (pos.makeMove(m)) {
        checkmate = false;
        value = min(value, minimax(pos, alfa, beta, depth - 1, true));
        beta = min(beta, value);
        pos.unmakeMove(m);
        if (alfa >= beta)
          break;
      }
    }
  }
  // väldigt fult
  if (checkmate) {
    if (pos.board.isAttacked(pos.turn == cWhite ? pos.board.getWhiteKing()
                                                : pos.board.getBlackKing(),
                             pos.turn == cWhite ? cBlack : cWhite))
      return 250 * (maximizingPlayer ? -1 : 1);
    else
      return 0;
  } else
    return value;
}

// https://www.chessprogramming.org/Evaluation
// Return value of position from current turns perspective
float valueOfPos(const Position &pos) {
  float value =
      9 * (countOnes(pos.board.getWhiteQueen()) -
           countOnes(pos.board.getBlackQueen())) +
      5 * (countOnes(pos.board.getWhiteRooks()) -
           countOnes(pos.board.getBlackRooks())) +
      3 * (countOnes(pos.board.getWhiteKnights()) -
           countOnes(pos.board.getBlackKnights()) +
           countOnes(pos.board.getWhiteBishops()) -
           countOnes(pos.board.getBlackBishops())) +
      (countOnes(pos.board.getWhitePawns() - pos.board.getBlackPawns()))
      // TODO: 0,5*(doubled, blocked and isolated pawns)
      ;

  // Mobilty heuristics
  vector<Move> whiteMoves, blackMoves;
  generateMoves(pos, whiteMoves, cWhite);
  generateMoves(pos, blackMoves, cBlack);
  value += 0.5 * (((float)whiteMoves.size()) - ((float)blackMoves.size()));

  /*
  if (value > 251) {
          std::cout << "v1 = " << v1 << " v2 = " << v2 << "value = " << value <<
  std::endl; std::cout << (float) whiteMoves.size() << " " << (float)
  blackMoves.size() << std::endl;
  }
  */
  return value * (currentTurn == cWhite ? 1 : -1);
}
