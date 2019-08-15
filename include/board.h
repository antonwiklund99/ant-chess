#ifndef BOARD_GUARD
#define BOARD_GUARD

#include <cstdint>
#include <iostream>
#include "piece.h"

typedef uint64_t Bitboard;

const Bitboard RANK_1 = 0x00000000000000ff;
const Bitboard RANK_2 = 0x000000000000ff00;
const Bitboard RANK_3 = 0x0000000000ff0000;
const Bitboard RANK_4 = 0x00000000ff000000;
const Bitboard RANK_5 = 0x000000ff00000000;
const Bitboard RANK_6 = 0x0000ff0000000000;
const Bitboard RANK_7 = 0x00ff000000000000;
const Bitboard RANK_8 = 0xff00000000000000;

//Bitboard bishopAttacks[2048];
//Bitboard rookAttacks[8196];

class Board {
 public:
  enum enumPiece {
                  nWhite,
                  nBlack,
                  nPawn,
                  nKnight,
                  nBishop,
                  nRook,
                  nQueen,
                  nKing,
  };

  friend std::ostream& operator<<(std::ostream&, const Bitboard&);

  // Get specific color
  Bitboard getWhites() const { return pieceBitboards[nWhite]; }
  Bitboard getBlacks() const { return pieceBitboards[nBlack]; }
  Bitboard getOccupied() const { return pieceBitboards[nWhite] | pieceBitboards[nBlack]; }
  Bitboard getEmpty() const { return ~(pieceBitboards[nWhite] | pieceBitboards[nBlack]); }

  // Get specific piece set
  Bitboard getWhitePawns() const { return pieceBitboards[nPawn] & pieceBitboards[nWhite]; }
  Bitboard getBlackPawns() const { return pieceBitboards[nPawn] & pieceBitboards[nBlack]; }
  Bitboard getWhiteKnights() const { return pieceBitboards[nKnight] & pieceBitboards[nWhite]; }
  Bitboard getBlackKnights() const { return pieceBitboards[nKnight] & pieceBitboards[nBlack]; }
  Bitboard getWhiteBishops() const { return pieceBitboards[nBishop] & pieceBitboards[nWhite]; }
  Bitboard getBlackBishops() const { return pieceBitboards[nBishop] & pieceBitboards[nBlack]; }
  Bitboard getWhiteRooks() const { return pieceBitboards[nRook] & pieceBitboards[nWhite]; }
  Bitboard getBlackRooks() const { return pieceBitboards[nRook] & pieceBitboards[nBlack]; }
  Bitboard getWhiteQueen() const { return pieceBitboards[nQueen] & pieceBitboards[nWhite]; }
  Bitboard getBlackQueen() const { return pieceBitboards[nQueen] & pieceBitboards[nBlack]; }
  Bitboard getWhiteKing() const { return pieceBitboards[nKing] & pieceBitboards[nWhite]; }
  Bitboard getBlackKing() const { return pieceBitboards[nKing] & pieceBitboards[nBlack]; }

  // Get ct color piece set
  Bitboard getSide(Color ct) const { return pieceBitboards[ct]; }
  Bitboard getPawns(Color ct) const { return pieceBitboards[nPawn] & pieceBitboards[ct]; }
  Bitboard getKnights(Color ct) const { return pieceBitboards[nKnight] & pieceBitboards[ct]; }
  Bitboard getBishops(Color ct) const { return pieceBitboards[nBishop] & pieceBitboards[ct]; }
  Bitboard getRooks(Color ct) const { return pieceBitboards[nRook] & pieceBitboards[ct]; }
  Bitboard getQueen(Color ct) const { return pieceBitboards[nQueen] & pieceBitboards[ct]; }
  Bitboard getKing(Color ct) const { return pieceBitboards[nKing] & pieceBitboards[ct]; }

  Board();
  void reset();
 private:
  // 0 - 1 = each colors bitboard
  // 2 - 7 = each piece types bitboard
  Bitboard pieceBitboards[8];

};

void initBitboards();
std::ostream& operator<<(std::ostream&, const Board&);

#endif
