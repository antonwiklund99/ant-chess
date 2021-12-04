#include "move.h"
#include <string>
using std::string;

string indexToCordinate(unsigned int i) {
  string ret;
  char file = (i % 8) + 'a';
  char rank = (i / 8) + '1';
  ret += file;
  ret += rank;
  return ret;
}

string Move::notation() const {
  string ret;
  ret = indexToCordinate(getFrom());
  ret += indexToCordinate(getTo());
  u_int flags = getFlags();
  if (flags == QUEEN_PROMOTION_FLAG || flags == QUEEN_PROMOTION_CAPTURE_FLAG) {
    ret += 'q';
  } else if (flags == ROOK_PROMOTION_FLAG || flags == ROOK_PROMOTION_CAPTURE_FLAG) {
    ret += 'r';
  } else if (flags == BISHOP_PROMOTION_FLAG || flags == BISHOP_PROMOTION_CAPTURE_FLAG) {
    ret += 'b';
  } else if (flags == KNIGHT_PROMOTION_FLAG || flags == KNIGHT_PROMOTION_CAPTURE_FLAG) {
    ret += 'n';
  }
  return ret;
}
