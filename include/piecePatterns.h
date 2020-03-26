#ifndef PATTERN_GUARD
#define PATTERN_GUARD

#include "board.h"

class PiecePatterns {
 public:
  static void initEasyBitboards();

  static Bitboard knight[64];
  static Bitboard king[64];
};

Bitboard noNoEa(Bitboard b);
Bitboard noEaEa(Bitboard b);
Bitboard soEaEa(Bitboard b);
Bitboard soSoEa(Bitboard b);
Bitboard noNoWe(Bitboard b);
Bitboard noWeWe(Bitboard b);
Bitboard soWeWe(Bitboard b);
Bitboard soSoWe(Bitboard b);
#endif
