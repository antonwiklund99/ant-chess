#include <iostream>
// #include <vector>
// #include <chrono>
#include "bitboards.h"
#include "board.h"
#include "enums.h"
#include "minimax.h"
#include "move.h"
#include "position.h"
// #include "utils.h"
#include "uci.h"

int main(int argc, char *argv[]) {
  UCI::run();
  // minimaxComputeBestMove(pos, 5);
  // std::cout <<
  // 	" wKing = " << pos.wKingsideCastling <<
  // 	" wQueensidecastling = " << pos.wQueensideCastling <<
  // 	" bKingsidecastling = " << pos.bKingsideCastling <<
  // 	" bQueensidecastling = " << pos.bQueensideCastling <<
  // 	" halfmovelcok = " << pos.halfMoveClock << std::endl;

  /*
  Position pos("1r3r2/ppp1kP1p/3pppp1/8/1BnP1P2/P3PK2/6NP/8 w KQkq - 0 1");
  initMagic();
  PiecePatterns::initEasyBitboards();
  std::cout << "turn=" << (pos.turn == cWhite ? "w" : "b") << std::endl;
  std::cout << pos.board;
  std::vector<Move> ps;
  generateMoves(pos, ps);
  std::vector<Move> x = legalMoves(pos);

  std::cout << "LEGAL:\n";
  for (auto& i: x) std::cout << i.notation() << std::endl;
  std::cout << "\nPSEUDO\n";
  for (auto& i: ps) std::cout << i.notation() << std::endl;

  int i = indexOf(ps, "f3g3");
  std::cout << i << std::endl;

  Move m = ps[i];
  std::cout << "FROM="<< m.getFrom() << std::endl;
  std::cout << "TO="<<m.getTo() << std::endl;
  std::cout << pos.makeMove(m) << std::endl;
  std::cout << pos.board;

            //Board b("rnb1kbnr/pppp1ppp/8/4p3/6q1/4P3/PPPP1PPP/RNB1KBNR");
Board b;
Position pos("r1b1k2r/ppppbppp/4p3/8/6K1/6P1/PP1n1P1P/nN6 w KQkq - 0 1");
  initMagic();
  PiecePatterns::initEasyBitboards();

  std::cout << pos.board;
  std::vector<Move> x = legalMoves(pos);
  std::vector<Move> x2;
  generateMoves(pos, x2);
  // GER INTE b1d2
  std::cout << "ALL" << std::endl;
  for (auto i: x) std::cout << i.notation() << std::endl;
  std::cout << "LEGAL" << std::endl;
  for (auto i: x2) std::cout << i.notation() << std::endl;

std::vector<Move> moveVec;
int n = 0;
while (n < 20 && legalMoves(pos).size() != 0) {
moveVec.clear();
generateMoves(pos, moveVec);
std::cout << pos.board << std::endl;
std::cout << "TURN = " << (pos.turn == cWhite ? "white" : "black") << std::endl;
std::cout << "LEGAL MOVES: " << std::endl;
for (auto i = 0; i < moveVec.size(); i++) {
std::cout << i << " " << moveVec[i].notation() << std::endl;
}

          //		if (pos.turn == cWhite) {
                  Move m = minimaxComputeBestMove(pos);
                  std::cout << "MINIMAX MOVE = " << m.notation() << std::endl;
                  std::string k = m.notation();
                  std::cout << "Move done succesfully? " << pos.makeMove(m) <<
"\n\n";
                  //		}

          else {

                  std::string k;
                  int i = -1;
                  printBitboardRows(pos.board.getBlackPawns());
                  do {
                          std::cout << "enter move: ";
                          std::cin >> k;
                          if (k == "quit") return 0;
                          i = indexOf(moveVec, k);
                  } while (i == -1);
                  Move& m = moveVec[i];
                  std::cout << "Move done succesfully? " << pos.makeMove(m) <<
"\n\n";
                  //}*/

  /*
  std::string k;
int i = -1;
do {
std::cout << "enter move: ";
std::cin >> k;
i = indexOf(moveVec, k);
} while (i == -1);
Move& m = moveVec[i];


std::cout << "Doing move " << k << ", at " << indexOf(moveVec, k) << " piece = "
<< m.piece << " color = " << m.color << " from = "
<< m.getFrom() << " to = " << m.getTo() << " cpiece = "
<< m.cPiece << " ccolor = " << m.cColor
<< std::endl;

n++;
}


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
auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>( t2 - t1
).count(); std::cout << "Average generateMoves = " << duration/100 << " ns\n";

std::cout << "1=" << pos.board.isAttacked(pos.board.getBlackQueen(), cWhite) <<
std::endl; std::cout << "0=" << pos.board.isAttacked(pos.board.getBlackKing(),
cWhite) << std::endl; std::cout << "1=" <<
pos.board.isAttacked(pos.board.getWhiteQueen(), cBlack) << std::endl; std::cout
<< pos.board.pieceOnSq(5) << std::endl;
*/
  return 0;
}
