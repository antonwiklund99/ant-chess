#ifndef BOARD_GUARD
#define BOARD_GUARD

#include <cstdint>
#include <iostream>
#include "piece.h"

typedef uint64_t Bitboard;

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
  /*
  Bitboard getPieceSet(const Piece& p) const {
    return pieceBitboards[p.type()] & pieceBitboards[p.color()];
  }
  */
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

std::ostream& operator<<(std::ostream&, const Board&);

#endif
