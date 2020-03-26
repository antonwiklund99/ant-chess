#ifndef MOVE_GUARD
#define MOVE_GUARD

#include <vector>
#include <string>
#include "enums.h"

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
            QUEEN_PROMOTION_CAPTURE_FLAG= 15
};

class Move {
public:
  Piece piece;
  Color color;
  Piece cPiece;
  Color cColor;

  Move(unsigned int from, unsigned int to, unsigned int flags, Piece p, Color c, Piece cp, Color cc)
    :piece(p), color(c), cPiece(cp), cColor(cc) {
    encodedMove = ((flags & 0xf) << 12) | ((from & 0x3f) << 6) | (to & 0x3f);
  }

  unsigned int getTo() const { return encodedMove & 0x3f; }
  unsigned int getFrom() const { return (encodedMove >> 6) & 0x3f; }
  unsigned int getFlags() const { return (encodedMove >> 12) & 0xf; }

  void setTo(unsigned int to) { encodedMove &= ~0x3f; encodedMove |= to & 0x3f; }
  void setFrom(unsigned int from) { encodedMove &= ~0xfc0; encodedMove |= (from & 0x3f) << 6; }
  void setFlags(unsigned int flags) { encodedMove &= ~0xf000; encodedMove |= (flags & 0xf) << 12; }

  // More is flags?
  bool isCapture() const { return encodedMove & (CAPTURE_FLAG << 12); }

  unsigned int getButterflyIndex() const { return encodedMove & 0x0fff; }
  void operator=(Move a) { encodedMove = a.encodedMove; }
  bool operator==(Move a) const { return (encodedMove & 0xffff) == (a.encodedMove & 0xffff); }
  bool operator!=(Move a) const { return (encodedMove & 0xffff) != (a.encodedMove & 0xffff); }

  std::string notation();

private:
  unsigned int encodedMove;
};

std::string indexToCordinate(unsigned int);
#endif
