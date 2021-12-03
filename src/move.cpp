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
  /*
  u_int flags = getFlags();
          lichess wants castling as king movement
          if (flags == KING_CASTLE_FLAG) return "0-0";
          if (flags == QUEEN_CASTLE_FLAG) return "0-0-0";
  */
  string ret;
  // if (piece != nPawn)
  ret = indexToCordinate(getFrom());
  // ret += ((isCapture()) ? 'x' : '-');
  ret += indexToCordinate(getTo());
  return ret;
}
