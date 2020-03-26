#include "piecePatterns.h"
#include "utils.h"

Bitboard PiecePatterns::knight[64] = {};
Bitboard PiecePatterns::king[64] = {};

void PiecePatterns::initEasyBitboards() {
  Bitboard b = 1;
  for (int i = 0; i != 64; ++i) {
    // Knight
    knight[i] = noNoEa(b) | noEaEa(b) | soEaEa(b) | soSoEa(b) |
         noNoWe(b) | noWeWe(b) | soWeWe(b) | soSoWe(b);

    // King
    king[i] = northOne(b) | southOne(b) | westOne(b) | eastOne(b) |
      southWestOne(b) | southEastOne(b) | northEastOne(b) | northWestOne(b);
    b <<= 1;
  }
}

Bitboard noNoEa(Bitboard b) { return (b & notHFile ) << 17; }
Bitboard noEaEa(Bitboard b) { return (b & (notGFile & notHFile)) << 10; }
Bitboard soEaEa(Bitboard b) { return (b & (notGFile & notHFile)) >>  6; }
Bitboard soSoEa(Bitboard b) { return (b & notHFile ) >> 15; }
Bitboard noNoWe(Bitboard b) { return (b & notAFile ) << 15; }
Bitboard noWeWe(Bitboard b) { return (b & (notAFile & notBFile)) <<  6; }
Bitboard soWeWe(Bitboard b) { return (b & (notAFile & notBFile)) >> 10; }
Bitboard soSoWe(Bitboard b) { return (b & notAFile ) >> 17; }
