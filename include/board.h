#ifndef BOARD_GUARD
#define BOARD_GUARD

#include "enums.h"
#include "move.h"
#include <iostream>
#include <string>

class Board {
public:
  friend std::ostream &operator<<(std::ostream &, const Bitboard &);

  // Get specific color
  Bitboard getWhites() const { return pieceBitboards[nWhite]; }
  Bitboard getBlacks() const { return pieceBitboards[nBlack]; }
  Bitboard getOccupied() const {
    return pieceBitboards[nWhite] | pieceBitboards[nBlack];
  }
  Bitboard getEmpty() const {
    return ~(pieceBitboards[nWhite] | pieceBitboards[nBlack]);
  }

  // Get specific piece set
  Bitboard getWhitePawns() const {
    return pieceBitboards[nPawn] & pieceBitboards[nWhite];
  }
  Bitboard getBlackPawns() const {
    return pieceBitboards[nPawn] & pieceBitboards[nBlack];
  }
  Bitboard getWhiteKnights() const {
    return pieceBitboards[nKnight] & pieceBitboards[nWhite];
  }
  Bitboard getBlackKnights() const {
    return pieceBitboards[nKnight] & pieceBitboards[nBlack];
  }
  Bitboard getWhiteBishops() const {
    return pieceBitboards[nBishop] & pieceBitboards[nWhite];
  }
  Bitboard getBlackBishops() const {
    return pieceBitboards[nBishop] & pieceBitboards[nBlack];
  }
  Bitboard getWhiteRooks() const {
    return pieceBitboards[nRook] & pieceBitboards[nWhite];
  }
  Bitboard getBlackRooks() const {
    return pieceBitboards[nRook] & pieceBitboards[nBlack];
  }
  Bitboard getWhiteQueen() const {
    return pieceBitboards[nQueen] & pieceBitboards[nWhite];
  }
  Bitboard getBlackQueen() const {
    return pieceBitboards[nQueen] & pieceBitboards[nBlack];
  }
  Bitboard getWhiteKing() const {
    return pieceBitboards[nKing] & pieceBitboards[nWhite];
  }
  Bitboard getBlackKing() const {
    return pieceBitboards[nKing] & pieceBitboards[nBlack];
  }

  // Get ct color piece set
  Bitboard getSide(Color ct) const { return pieceBitboards[ct]; }
  Bitboard getPawns(Color ct) const {
    return pieceBitboards[nPawn] & pieceBitboards[ct];
  }
  Bitboard getKnights(Color ct) const {
    return pieceBitboards[nKnight] & pieceBitboards[ct];
  }
  Bitboard getBishops(Color ct) const {
    return pieceBitboards[nBishop] & pieceBitboards[ct];
  }
  Bitboard getRooks(Color ct) const {
    return pieceBitboards[nRook] & pieceBitboards[ct];
  }
  Bitboard getQueen(Color ct) const {
    return pieceBitboards[nQueen] & pieceBitboards[ct];
  }
  Bitboard getKing(Color ct) const {
    return pieceBitboards[nKing] & pieceBitboards[ct];
  }

  Board();
  Board(std::string);
  void reset();
  bool isAttacked(Bitboard, Color) const;
  void unsafeMakeMove(const Move &);
  Piece pieceOnSq(int) const;

private:
  // 0 - 1 = each colors bitboard
  // 2 - 7 = each piece types bitboard
  Bitboard pieceBitboards[8];
};

Bitboard wSinglePush(Bitboard, Bitboard);
Bitboard bSinglePush(Bitboard, Bitboard);
Bitboard wDoublePush(Bitboard, Bitboard);
Bitboard bDoublePush(Bitboard, Bitboard);

Bitboard wPawnEastAttack(Bitboard, Bitboard);
Bitboard wPawnWestAttack(Bitboard, Bitboard);
Bitboard bPawnEastAttack(Bitboard, Bitboard);
Bitboard bPawnWestAttack(Bitboard, Bitboard);

std::ostream &operator<<(std::ostream &, const Board &);
#endif
