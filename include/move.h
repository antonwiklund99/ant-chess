#ifndef MOVE_GUARD
#define MOVE_GUARD

#include <vector>
#include <string>
#include "position.h"
#include "piece.h"

enum flags {
            QUIET_MOVE_FLAG = 0,
            DOUBLE_PAWN_PUSH_FLAG = 1,
            KING_CASTLE_FLAG = 2,
            QUEEN_CASTLE_FLAG = 3,
            CAPTURE_FLAG = 4,
            EP_CAPTURE_FLAG = 5,
            KNIGHT_PROMOTION_FLAG = 8,
            BISHOP_PROMOTION_FLAG = 9,
            ROOK_PROMOTION_FLAG = 10,
            QUEEN_PROMOTION_FLAG= 11,
            KNIGHT_PROMOTION_CAPTURE_FLAG = 12,
            BISHOP_PROMOTION_CAPTURE_FLAG = 13,
            ROOK_PROMOTION_CAPTURE_FLAG = 14,
            QUEEN_PROMOTION_CAPTURE_FLAG= 15,
};
class Move {
public:
  Move(unsigned int from, unsigned int to, unsigned int flags) {
    encodedMove = ((flags & 0xf) << 12) | ((from & 0x3f) << 6) | (to & 0x3f);
  }
  void operator=(Move a) {encodedMove = a.encodedMove; }

  unsigned int getTo() const { return encodedMove & 0x3f; }
  unsigned int getFrom() const { return (encodedMove >> 6) & 0x3f; }
  unsigned int getFlags() const { return (encodedMove >> 12) & 0xf; }

  void setTo(unsigned int to) { encodedMove &= ~0x3f; encodedMove |= to & 0x3f; }
  void setFrom(unsigned int from) { encodedMove &= ~0xfc0; encodedMove |= (from & 0x3f) << 6; }
  void setFlags(unsigned int flags) { encodedMove &= ~0xf000; encodedMove |= (flags & 0xf) << 12; }

  // More is flags?
  bool isCapture() const { return encodedMove & (CAPTURE_FLAG << 12); }

  unsigned int getButterflyIndex() const { return encodedMove & 0x0fff; }
  bool operator==(Move a) const { return (encodedMove & 0xffff) == (a.encodedMove & 0xffff); }
  bool operator!=(Move a) const { return (encodedMove & 0xffff) != (a.encodedMove & 0xffff); }

  std::string notation();

private:
  unsigned int encodedMove;
};

void generateMoves(const Position&, std::vector<Move>&, Color);

Bitboard wSinglePush(Bitboard, Bitboard);
Bitboard bSinglePush(Bitboard, Bitboard);
Bitboard wDoublePush(Bitboard, Bitboard);
Bitboard bDoublePush(Bitboard, Bitboard);

Bitboard northOne(Bitboard);
Bitboard southOne(Bitboard);

const int index64[64] = {
    0,  1, 48,  2, 57, 49, 28,  3,
   61, 58, 50, 42, 38, 29, 17,  4,
   62, 55, 59, 36, 53, 51, 43, 22,
   45, 39, 33, 30, 24, 18, 12,  5,
   63, 47, 56, 27, 60, 41, 37, 16,
   54, 35, 52, 21, 44, 32, 23, 11,
   46, 26, 40, 15, 34, 20, 31, 10,
   25, 14, 19,  9, 13,  8,  7,  6
};
int bitScanForward(Bitboard);
std::string indexToCordinate(unsigned int);
#endif
