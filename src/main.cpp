#include <iostream>
#include <vector>
#include <chrono>
#include "position.h"
#include "board.h"
#include "move.h"
#include "piecePatterns.h"
#include "magic.h"
#include "minimax.h"
#include "utils.h"

int indexOf(std::vector<Move> &v, std::string& s) {
  for (int i = 0; i < v.size(); i++) {
    std::cout << "s " << s << " v " << v[i].notation() << " " << v[i].notation().compare(s) << std::endl;

    if (v[i].notation().compare(s) == 0) return i;
  }
  return -1;
}

int main(int argc, char *argv[])
{
  //Board b("rnb1kbnr/ppp1pppp/8/3p4/q7/2P2P2/PP1PP1PP/RNBQKBNR");
  Board b;
  Position pos(b, cWhite, true, true, 1);
  PiecePatterns::initEasyBitboards();
  initMagic();

  std::vector<Move> moveVec;
  int n = 0;
  while (true && n < 1000) {
    moveVec.clear();
    generateMoves(pos, moveVec);
    std::cout << pos.board << std::endl;
    std::cout << "TURN = " << (pos.turn == cWhite ? "white" : "black") << std::endl;
    std::cout << "LEGAL MOVES: " << std::endl;
    for (int i = 0; i < moveVec.size(); i++) {
      std::cout << i << " " << moveVec[i].notation() << std::endl;
    }
    Move m = minimaxComputeBestMove(pos);
    std::cout << "MINIMAX MOVE = " << m.notation() << std::endl;
    std::string k = m.notation();

    /*
    int i = -1;
    do {
      std::cout << "enter move: ";
      std::cin >> k;
      i = indexOf(moveVec, k);
    } while (i == -1);
    Move& m = moveVec[i];
    */
    std::cout << "Doing move " << k << ", at " << indexOf(moveVec, k) << " piece = "
              << m.piece << " color = " << m.color << " from = "
              << m.getFrom() << " to = " << m.getTo() << " cpiece = "
              << m.cPiece << " ccolor = " << m.cColor
              << std::endl;
    std::cout << "Move done succesfully? " << pos.makeMove(m) << "\n\n";
    n++;
  }

  /*
  Magic t = Magic::bishopTable[20];
  std::cout << "MAGIC\n";
  printBitboardRows(t.magic);
  std::cout << "MASK\n";
  printBitboardRows(t.mask);
  std::cout << "SHIFT\n" << t.shift << "\nUSED[BLOCK]\n";
  Bitboard occ = pos.board.getOccupied() & t.mask;
  std::cout << "OCC\n";
  printBitboardRows(occ);
  std::cout << "i = " << transform(occ, t.magic, t.shift) << std::endl;
  printBitboardRows(t.ptr[transform(occ, t.magic, t.shift)]);
  printBitboardRows(bishopAttacks(20, occ));
  std::vector<Move> moveVec;


  auto t1 = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < 100; i++) {
    generateMoves(pos, moveVec);
  }
  auto t2 = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>( t2 - t1 ).count();
  std::cout << "Average generateMoves = " << duration/100 << " ns\n";

  std::cout << "1=" << pos.board.isAttacked(pos.board.getBlackQueen(), cWhite) << std::endl;
  std::cout << "0=" << pos.board.isAttacked(pos.board.getBlackKing(), cWhite) << std::endl;
  std::cout << "1=" << pos.board.isAttacked(pos.board.getWhiteQueen(), cBlack) << std::endl;
  std::cout << pos.board.pieceOnSq(5) << std::endl;
  */
  return 0;
}
