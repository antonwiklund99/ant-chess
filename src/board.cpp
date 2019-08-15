#include <iostream>
#include <bitset>
#include "board.h"
using std::ostream;

Board::Board() {
  reset();
}

void Board::reset() {
  pieceBitboards[0] = 0x000000000000ffff;
  pieceBitboards[1] = 0xffff000000000000;
  pieceBitboards[2] = 0x00ff00000000ff00;
  pieceBitboards[3] = 0x4200000000000042;
  pieceBitboards[4] = 0x2400000000000024;
  pieceBitboards[5] = 0x8100000000000081;
  pieceBitboards[6] = 0x0800000000000008;
  pieceBitboards[7] = 0x1000000000000010;
}

void initBitboards() {
  //https://www.chessprogramming.org/Magic_Bitboards
}
// Cout bitboard
ostream& operator<<(ostream& os, const Board& b) {
  Bitboard mask = 1;
  for (int i = 0; i < 64; i++) {
    //os << std::bitset<64>(mask) << std::endl;
    if (b.getWhitePawns() & mask)
      os << "p ";
    else if (b.getBlackPawns() & mask)
      os << "P ";
    else if (b.getWhiteKnights() & mask)
      os << "n ";
    else if (b.getBlackKnights() & mask)
      os << "N ";
    else if (b.getWhiteBishops() & mask)
      os << "b ";
    else if (b.getBlackBishops() & mask)
      os << "B ";
    else if (b.getWhiteRooks() & mask)
      os << "r ";
    else if (b.getBlackRooks() & mask)
      os << "R ";
    else if (b.getWhiteQueen() & mask)
      os << "q ";
    else if (b.getBlackQueen() & mask)
      os << "Q ";
    else if (b.getWhiteKing() & mask)
      os << "k ";
    else if (b.getBlackKing() & mask)
      os << "K ";
    else
      os << "0 ";

    mask <<= 1;
    if ((i + 1) % 8 == 0)
      os << "\n";
  }
  return os;
}

Bitboard northOne(Bitboard b) { return b << 8; }
Bitboard southOne(Bitboard b) { return b >> 8; }

Bitboard westOne(Bitboard b) { return (b & notAFile) >> 1; }
Bitboard southWestOne(Bitboard b) { return (b & notAFile) >> 9; }
Bitboard northWestOne(Bitboard b) { return (b & notAFile) << 7; }

Bitboard eastOne(Bitboard b) { return (b & notHFile) << 1; }
Bitboard southEastOne(Bitboard b) { return (b & notHFile) >> 7; }
Bitboard northEastOne(Bitboard b) { return (b & notHFile) << 9; }
